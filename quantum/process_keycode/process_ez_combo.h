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

#pragma once

#define EZ_COMBO_ENABLE 1

#include <stdint.h>
#include <stdbool.h>
#include "action.h"

// ez combos will only ever be two key combos
#define MAX_EZ_COMBO_LENGTH 2

typedef struct ez_combo_t {
    // keys that will activate the combo
    const uint16_t* keys;

    // keycode that the combo emits
    uint16_t keycode;

    // true when the combo is activated, false when key_down is all false
    bool active;

    // all true when activated, when active, false as key ups are
    // seen, each index corresponds to the same index in `keys`
    bool key_down[MAX_EZ_COMBO_LENGTH];
} ez_combo_t;

// Activate a combo and set all of it's key downs to true. Noop if
// combo is active.
void ez_combo_activate(uint16_t combo_index, ez_combo_t* combo);
// Deactivate a combo and set all of it's key downs to false. Noop if
// combo is not active.
void ez_combo_deactivate(uint16_t combo_index, ez_combo_t* combo);
// Set key_down for the keycode to false, if all keys are released,
// the combo is also deactivated. Returns true if the combo key down
// was changed to false, false otherwise. Noop and returns false if
// the combo is not active.
bool ez_combo_key_release(uint16_t combo_index, ez_combo_t* combo, uint16_t keycode);

// Main entry point
bool process_ez_combo(uint16_t keycode, keyrecord_t* record);

// Matrix scan task
void ez_combo_task(void);
