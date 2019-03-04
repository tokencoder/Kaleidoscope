/* -*- mode: c++ -*-
 * Kaleidoscope-Hardware-OLKB-Imago -- Imago hardware support for Kaleidoscope
 * Copyright (C) 2018  Keyboard.io, Inc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef ARDUINO_AVR_KEYBOARDIO_IMAGO

#include <Kaleidoscope.h>
#include <avr/wdt.h>

namespace kaleidoscope {
namespace hardware {
namespace keyboardio {

ATMEGA_KEYBOARD_DATA(Imago);
constexpr int8_t Imago::led_count;
bool Imago::isLEDChanged = true;

static constexpr int8_t key_led_map[4][16] PROGMEM = {
  {3, 4, 11, 12, 19, 20, 26, 27,     36, 37, 43, 44, 51, 52, 59, 60},
  {2, 5, 10, 13, 18, 21, 25, 28,     35, 38, 42, 45, 50, 53, 58, 61},
  {1, 6, 9, 14, 17, 22, 24, 29,     34, 39, 41, 46, 49, 54, 57, 62},
  {0, 7, 8, 15, 16, 23, 31, 30,     33, 32, 40, 47, 48, 55, 56, 63},
};

void Imago::initLeds(){ 
    digitalWrite(MOSI, HIGH);
    digitalWrite(SS, HIGH);
    uint8_t twi_uninitialized = 1;
    if (twi_uninitialized--) {
        twi_init();
    }
    TWBR=10;

}


void Imago::setCrgbAt(int8_t i, cRGB crgb) {
  if (i < 0) {
    return;
  }
  if (i < led_count) {
    cRGB oldColor = getCrgbAt(i);
    isLEDChanged |= !(oldColor.r == crgb.r && oldColor.g == crgb.g && oldColor.b == crgb.b);

    led_data[i] = crgb;
  }
}

void Imago::setCrgbAt(byte row, byte col, cRGB color) {
  setCrgbAt(getLedIndex(row, col), color);
}

int8_t Imago::getLedIndex(byte row, byte col) {
  return pgm_read_byte(&(key_led_map[row][col]));
}


cRGB Imago::getCrgbAt(int8_t i) {
  if (i < 0 || i > led_count)
    return {0, 0, 0};

  return led_data[i];
}

void Imago::syncLeds() {
  if (!isLEDChanged)
    return;

    uint8_t data[0xB5] = {};
    data[0]=0;
    uint8_t last_led =0;
    for(auto i=1; i<0xB4; i+=3) {
        data[i] = led_data[last_led].b;
        data[i+1] =led_data[last_led].g;
        data[i+2] = led_data[last_led].r;
	last_led++;
    }
     twi_writeTo(ADDR_IS31/2, data, 0xB5, 1, 0);



  isLEDChanged = false;
}


}
}
}

HARDWARE_IMPLEMENTATION KeyboardHardware;
kaleidoscope::hardware::keyboardio::Imago &Imago = KeyboardHardware;

#endif
