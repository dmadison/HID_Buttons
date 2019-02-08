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
 *  Example:      DoubleClick
 *  Description:  When a pin is grounded, click the mouse twice at the speed
 *                of a double click
 *
 */

#include <Mouse.h>  // Use built-in Mouse library
#include <HID_Buttons.h>  // Must import AFTER Mouse.h

const uint8_t ButtonPin = 6;  // Pin for hardware button

MouseButton leftClick(MOUSE_LEFT);

void setup() {
	pinMode(ButtonPin, INPUT_PULLUP);
	Mouse.begin();
}

void loop() {
	boolean pressed = !digitalRead(ButtonPin);

	if (pressed == true) {
		leftClick.write();  // Press & release
		delay(125);         // Delay for a "double click" time
		leftClick.write();  // Press & release again
		delay(250);         // Don't spam!
	}
}
