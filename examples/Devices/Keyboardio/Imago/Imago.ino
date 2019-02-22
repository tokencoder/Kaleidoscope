/* -*- mode: c++ -*-
 * Imago -- A very basic Kaleidoscope example for the Keyboardio Imago Planck keyboard
 * Copyright (C) 2018  Keyboard.io,	Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License,	or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,	
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTabILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not,	write to the Free Software Foundation,	Inc.,	
 * 51 Franklin Street,	Fifth Floor,	Boston,	MA 02110-1301 USA.
 */

#include "Kaleidoscope.h"
#include "Kaleidoscope-Macros.h"

enum {  _QWERTY,	
     };


/* *INDENT-OFF* */
KEYMAPS( 

/* Qwerty
 * ,	-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,	|   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */

[_QWERTY] = KEYMAP(

Key_1, Key_2, Key_3, Key_4, Key_5, Key_6, Key_7, Key_8, Key_9, Key_0, Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, 
XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,




/*
[_QWERTY] = KEYMAP(

Key_1, Key_Escape,	Key_Backtick,		Key_1,		Key_2,	 	Key_3,	Key_4,	   Key_5, Key_6,	 Key_7,	        Key_9,	    Key_0,	Key_Equals,	Key_Backspace,	___,
Key_2, Key_Tab,	Key_Q,	 		Key_W,		Key_E,	 	Key_R,	Key_T,	   Key_Y, Key_U,	 Key_I,	        Key_O,	    Key_P,	 Key_Backspace,	___,	
Key_3, Key_Escape,	Key_A,	 		Key_S,	 	Key_D,	 	Key_F,	Key_G,	   Key_H, Key_J,	 Key_K,	        Key_L,	    Key_Semicolon,	Key_Quote,	___ ,___,	
Key_4, Key_LeftShift,	Key_Z,	 		Key_X,	 	Key_C,	 	Key_V,	Key_B,	   Key_N, Key_M,	 Key_Comma,	Key_Period,	Key_Slash,	Key_Enter ,	___,	
Key_5, ___,		Key_LeftControl,	Key_LeftAlt,	Key_LeftGui,	___,	Key_Space,  ___,  Key_LeftArrow, Key_DownArrow,	Key_UpArrow,	Key_RightArrow, ___, ___, ___

*/

));
/* *INDENT-ON* */

KALEIDOSCOPE_INIT_PLUGINS(Macros);

void setup() {
  Kaleidoscope.setup();
  Serial.begin(9600);
}

void loop() {
  Kaleidoscope.loop();
}
