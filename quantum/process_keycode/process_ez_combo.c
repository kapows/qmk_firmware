/* Copyright 2023 Peter Kheo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "process_ez_combo.h"

#include <stddef.h>

#include "timer.h"
#include "keymap_introspection.h"

// TODO REMOVE THIS
static uint16_t ez_combo_size = 10;

//* System

//** Timer
static uint16_t timer = 0;

//** Active combos
//
// Active combos is an unordered dynamic array of combos that are
// active.

// Maximum number of active combos
#define MAX_ACTIVE_COMBOS 8
// Active combo index buffer
static uint16_t active_combos[MAX_ACTIVE_COMBOS];
// Number of active combos
static uint8_t active_combos_size = 0;

// Add a combo to the active combo array if the it isn't full. Returns
// true if the is not full and the combo was added, false
// otherwise.
static inline bool active_combo_add(uint16_t combo_index) {
    bool is_not_full = active_combos_size < MAX_ACTIVE_COMBOS;
    if (is_not_full) {
        active_combos[active_combos_size++] = combo_index;
    }
    return is_not_full;
}
// Ensures that the combo is no longer in the active combo list.
static inline void active_combo_remove(uint16_t combo_index) {
    for (uint8_t i = 0; i < active_combos_size; ++i) {
        if (active_combos[i] == combo_index) {
            // copy the combo at the back of the list into the
            // matching combos place and reduce the size of the list
            active_combos[i] = active_combos[active_combos_size--];
            break;
        }
    }
}

// Handle key release for active combos. True
// if an active combo key was released, false otherwise.
static bool active_combo_key_release(uint16_t keycode, keyrecord_t* record) {
    for (uint16_t i = 0; i < active_combos_size; ++i) {
        ez_combo_t* combo = ez_combo_get(i);
        if (ez_combo_key_release(i, combo, keycode)) {
            return true;
        }
    }
    return false;
}

//** Hot Combo
//
// The hot combo is the only combo that can be activated with the
// current keys inside of the key queue. One key will be the first
// element in the queue and the second will be somewhere in the queue.

// Index of the combo.
static uint16_t hot_combo_index = -1;

static inline void clear_hot_combo() {
    hot_combo_index = -1;
}

// Test if hot combo has been set. True if it is, false otherwise.
static inline bool hot_combo_set(void) {
    return hot_combo_index != (uint16_t)-1;
}

//** Key queue
//
// Key queue is implemented as a circular queue. The first element in
// the queue will always be a key down. The last element can be either
// a key up or a key down. All elements between first and last will be
// key ups.
//
// (0) | D U U U U D |
// or
// (1) | D U U D U U |
// or
// (2) | D U U U U U |
//
// If (0) or (1) then a hot combo will be set, this combo must use
// both of the key down events in the key queue. If (2) there is no
// hot combo. The hot combo is the only combo that can be activated
// with the keys in the key queue.

// Maximum number of elements that the queue can hold. This must be a
// power of 2 and less then uint8 max for the proper operation of a
// circular queue.
#define MAX_KEY_QUEUE_SIZE 8

// Key queue elements hold all of the information that was passed into
// ez_combo for the key event.
typedef struct {
    keyrecord_t record;
    uint16_t    keycode;
} key_queue_elem_t;
// The key queue
static key_queue_elem_t key_queue[MAX_KEY_QUEUE_SIZE];
// The index of the first element of the key queue
static uint8_t key_queue_first = 0;
// The index that is one passed the last element of the key queue
static uint8_t key_queue_last = 0;

//*** Queue primitives
//
// These should be used to access the key queue, it should never be
// used directly.

// Access the first element of the key queue
static inline key_queue_elem_t* key_queue_peek(void) {
    return &key_queue[key_queue_first % MAX_KEY_QUEUE_SIZE];
}
// Add an element to the back of the key queue
static inline void key_queue_enqueue(uint16_t keycode, keyrecord_t* record) {
    key_queue[key_queue_last++ % MAX_KEY_QUEUE_SIZE] = (key_queue_elem_t){.record = *record, .keycode = keycode};
}
// Remove the first element of the key queue
static inline void key_queue_dequeue(void) {
    ++key_queue_first;
}
// Test if the key queue is empty
static inline bool key_queue_empty(void) {
    return key_queue_last == key_queue_first;
}
// Number of elements in the key queue
static inline uint8_t key_queue_size(void) {
    return key_queue_last - key_queue_first;
}

//** System Primitives

// Consumes the first element in the key queue
static inline void eat(void) {
    key_queue_dequeue();
}
// Releases the first element in the key queue back to the wild
static inline void discard(void) {
    process_record(&key_queue_peek()->record);
    key_queue_dequeue();
}

//** System interface

// Test if the system has been started with a pressed element.
static inline bool in_play(void) {
    return !key_queue_empty();
}
// The keycode of the first pressed element that was added to the
// system. Undefined if not in play.
static inline uint16_t keycode_in_play(void) {
    return key_queue_peek()->keycode;
}
// The keycode of the second pressed element that was added to the
// system. Undefined if not able to be activated.
static inline uint16_t second_keycode_in_play() {
    ez_combo_t* combo = ez_combo_get(hot_combo_index);
    return keycode_in_play() == combo->keys[0] ? combo->keys[1] : combo->keys[0];
}

// Process key releases from the beginning of
// the queue to a key press or the end of the queue. Key releases of
// active combos will be used by the system. Other key releases are
// discarded.
static void process_queued_key_releases(void) {
    while (!key_queue_empty() && !key_queue_peek()->record.event.pressed) {
        key_queue_elem_t* x = key_queue_peek();
        if (active_combo_key_release(x->keycode, &x->record)) {
            eat();
        } else {
            discard();
        }
    }
}

// Drop the hot combo and handle all the other elements in the key
// queue. If there was a hot combo, there will be one element left in
// the queue and it will be a key down. If there was no hot combo then
// the queue will be empty. Undefined if not in play.
static void drop(void) {
    clear_hot_combo();
    discard();
    process_queued_key_releases();
}

// Activate the hot combo, takes it's keys and handle all the other
// elements in the system. The system will be emptied. Undefined if
// hot_combo_index is -1 is false. Undefined if not in play.
static void activate(void) {
    eat();
    process_queued_key_releases();
    eat();
    process_queued_key_releases();

    ez_combo_activate(hot_combo_index, ez_combo_get(hot_combo_index));
    clear_hot_combo();
}

// Test if the system is full. Returns true if full, false otherwise.
static inline bool full() {
    return key_queue_size() == MAX_KEY_QUEUE_SIZE;
}

// Add an element to the system. Returns true if the system did
// something with the element, false otherwise. Undefined if the
// system is already full.
static bool feed(uint16_t keycode, keyrecord_t* record) {
    if (in_play()) {
        key_queue_enqueue(keycode, record);
        return true;
    } else if (record->event.pressed) {
        key_queue_enqueue(keycode, record);
        return true;
    } else if (active_combo_key_release(keycode, record)) {
        return true;
    } else {
        return false;
    }
}

static bool process_key(uint16_t keycode, keyrecord_t* record) {
    bool key_pressed = record->event.pressed;
    if (hot_combo_set()) {
        // full queue
        if (full()) {
            drop();
            return process_key(keycode, record);
        }
        // key press
        else if (key_pressed) {
            drop();
            return process_key(keycode, record);
        }
        // key release of first combo keycode
        else if (keycode == keycode_in_play()) {
            drop();
            return process_key(keycode, record);
        }
        // key release of second combo keycode
        else if (keycode == second_keycode_in_play()) {
            drop();
            drop();
            timer = 0;
            return false;
        }
        // key release of any other key
        else {
            return feed(keycode, record);
        }
    } else if (in_play()) {
        // full queue
        if (full()) {
            drop();
            return process_key(keycode, record);
        }
        // key press
        else if (key_pressed) {
            uint16_t combo_index = -1;
            // find a combo that matches with the keycode in play and the new keycode
            uint16_t k = keycode_in_play();
            for (uint16_t i = 0; i < ez_combo_size; ++i) {
                ez_combo_t* combo = ez_combo_get(i);
                if (!combo->active && ((k == combo->keys[0] && keycode == combo->keys[1]) || (k == combo->keys[1] && keycode == combo->keys[0]))) {
                    combo_index = i;
                    break;
                }
            }

            if (combo_index != (uint16_t)-1) {
                feed(keycode, record);
                hot_combo_index = combo_index;
                timer           = record->event.time;
                return true;
            } else {
                drop();
                return process_key(keycode, record);
            }
        }
        // key release of combo first keycode
        else if (keycode == keycode_in_play()) {
            drop();
            return false;
        }
        // key release of any other keycode
        else {
            return feed(keycode, record);
        }
    } else {
        if (key_pressed) {
            uint16_t combo_index = -1;
            // find a combo that matches with the new keycode
            for (uint16_t i = 0; i < ez_combo_size; ++i) {
                ez_combo_t* combo = ez_combo_get(i);
                if (!combo->active && ((keycode == combo->keys[0]) || (keycode == combo->keys[1]))) {
                    combo_index = i;
                    break;
                }
            }
            if (combo_index != (uint16_t)-1) {
                feed(keycode, record);
                timer = record->event.time;
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
}

void ez_combo_activate(uint16_t combo_index, ez_combo_t* combo) {
    if (!combo->active) {
        combo->key_down[0] = combo->key_down[1] = true;
        combo->active                           = true;
        active_combo_add(combo_index);
    }
}
void ez_combo_deactivate(uint16_t combo_index, ez_combo_t* combo) {
    if (combo->active) {
        combo->key_down[0] = combo->key_down[1] = false;
        combo->active                           = false;
        active_combo_remove(combo_index);
    }
}
bool ez_combo_key_release(uint16_t combo_index, ez_combo_t* combo, uint16_t keycode) {
    if (!combo->active) {
        return false;
    }
    bool key_released = false;
    if (combo->keys[0] == keycode) {
        combo->key_down[0] = false;
        key_released       = true;
    } else if (combo->keys[1] == keycode) {
        combo->key_down[1] = false;
        key_released       = true;
    }
    if (key_released && combo->key_down[0] == false && combo->key_down[1] == false) {
        ez_combo_deactivate(combo_index, combo);
    }
}

bool process_ez_combo(uint16_t keycode, keyrecord_t* record) {
    bool handled = false;

    handled = process_key(keycode, record);

    return handled;
}

void ez_combo_task(void) {
    if (timer && timer_elapsed(timer) > 50) {
        if (hot_combo_set()) {
            activate();
        } else {
            drop();
        }
        timer = 0;
    }
}
