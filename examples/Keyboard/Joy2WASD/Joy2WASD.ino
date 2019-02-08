/*
 *  Project     HID Buttons Library
 *  @author     David Madison
 *  @link       github.com/dmadison/HID_Buttons
 *  @license    MIT - Copyright (c) 2019 David Madison
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *  Example:      Joy2WASD
 *  Description:  Using a joystick connected to two analog inputs, convert
 *                the output to "WASD" keys typically used for movement
 *                in PC games.
 *
 *                Note that the Y axis logic is inverted so a 'low' value
 *                is move forward. This matches the generic analog joysticks
 *                I have on hand.
 *
 */

#include <Keyboard.h>  // Use built-in Keyboard library
#include <HID_Buttons.h>  // Must import AFTER Keyboard.h

const uint8_t Pin_XAxis = A0;  // Pin for joy horizontal axis
const uint8_t Pin_YAxis = A1;  // Pin for joy vertical axis

const int JoyCenter   = 1023 / 2;  // max value for 10-bit ADC / 2
const int JoyDeadzone = 50;        // +/- area around the center to ignore

KeyboardButton moveForward('w');
KeyboardButton moveLeft('a');
KeyboardButton moveBackward('s');
KeyboardButton moveRight('d');

void setup() {
	Keyboard.begin();
}

void loop() {
	int x = analogRead(Pin_XAxis);  // Read X axis
	int y = analogRead(Pin_YAxis);  // Read Y axis

	moveLeft.set(x < JoyCenter - JoyDeadzone);
	moveRight.set(x > JoyCenter + JoyDeadzone);

	moveForward.set(y < JoyCenter - JoyDeadzone);
	moveBackward.set(y > JoyCenter + JoyDeadzone);
}
