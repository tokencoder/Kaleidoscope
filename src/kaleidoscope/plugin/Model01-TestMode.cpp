/* Kaleidoscope-Model01-TestMode - A factory test mode for the Model 01.
 * Copyright (C) 2017-2018  Keyboard.io, Inc.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#if ARDUINO_AVR_MODEL01

#include "Kaleidoscope.h"
#include "Kaleidoscope-Model01-TestMode.h"
#include "Kaleidoscope-LEDEffect-Rainbow.h"

namespace kaleidoscope {
namespace plugin {


constexpr uint8_t CHATTER_CYCLE_LIMIT = 30;

uint8_t TestMode::actionKey;

void TestMode::setActionKey(uint8_t key) {
  actionKey = key; 
}

void TestMode::waitForKeypress() {
  while (1) {
    KeyboardHardware.readMatrix();
    if (KeyboardHardware.isKeyswitchPressed(actionKey) && 
	! KeyboardHardware.wasKeyswitchPressed(actionKey)) {
      break;
    }
  }
}

void TestMode::setLeds(cRGB color) {
  ::LEDControl.set_all_leds_to(color);
  ::LEDControl.syncLeds();
  waitForKeypress();
}

void TestMode::testLeds(void) {
  constexpr cRGB red = CRGB(201, 0, 0);
  constexpr cRGB blue = CRGB(0, 0, 201);
  constexpr cRGB green = CRGB(0, 201, 0);
  constexpr cRGB brightWhite = CRGB(160, 160, 160);

  // rainbow for 10 seconds
  for (auto i = 0; i < 1000; i++) {
    ::LEDRainbowEffect.update();
    ::LEDControl.syncLeds();
  }
  setLeds(brightWhite);
  setLeds(blue);
  setLeds(green);
  setLeds(red);
}



void TestMode::testMatrix() {
  // Reset bad keys from previous tests.
  chatter_data state[KeyboardHardware.matrix_columns * KeyboardHardware.matrix_rows] = {0,0};

  constexpr cRGB red = CRGB(201, 0, 0);
  constexpr cRGB blue = CRGB(0, 0, 201);
  constexpr cRGB green = CRGB(0, 201, 0);
  constexpr cRGB white = CRGB(160, 160, 160);

  while (1) {
    KeyboardHardware.readMatrix();
    for (byte row = 0; row < KeyboardHardware.matrix_rows; row++) {
      for (byte col = 0; col < KeyboardHardware.matrix_columns; col++) {
        uint8_t keynum = (row * KeyboardHardware.matrix_columns) + (col);

	// If the key is toggled on
        if (KeyboardHardware.isKeyswitchPressed(row, col) && ! KeyboardHardware.wasKeyswitchPressed(row, col)) {
          // And it's too soon (in terms of cycles between changes)
          if (state[keynum].cyclesSinceStateChange < CHATTER_CYCLE_LIMIT) {
            state[keynum].bad = 1;
          }
          state[keynum].cyclesSinceStateChange = 0;
        } else if (state[keynum].cyclesSinceStateChange < CHATTER_CYCLE_LIMIT) {
          state[keynum].cyclesSinceStateChange++;
        }
        // If the key is toggled on or off, make the key white
	if (KeyboardHardware.isKeyswitchPressed(row, col) != KeyboardHardware.wasKeyswitchPressed(row, col)) { 
          KeyboardHardware.setCrgbAt(row, col, white);
	} 
        // If the key is held down
        else if (KeyboardHardware.isKeyswitchPressed(row, col) && KeyboardHardware.wasKeyswitchPressed(row, col)) {
          KeyboardHardware.setCrgbAt(row, col, green);
        } 

        // If we triggered chatter detection ever on this key
	else if (state[keynum].bad == 1) {
          KeyboardHardware.setCrgbAt(row, col, red);
        } 
        // If the key is not currently pressed and was not just released and is not marked bad
        else if ( ! KeyboardHardware.isKeyswitchPressed(row, col)) {
          KeyboardHardware.setCrgbAt(row, col, blue);
	}
      }
    }
    ::LEDControl.syncLeds();
  }
}

void TestMode::runTests() {
  KeyboardHardware.enableHardwareTestMode();
  testLeds();
  testMatrix();
}

}
}

kaleidoscope::plugin::TestMode TestMode;

#endif
