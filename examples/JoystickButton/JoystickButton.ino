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
 *  Example:      JoystickButton
 *  Description:  Use the HID Buttons library with Joystick buttons. Requires the
 *                Arduino Joystick library:
 *                https://github.com/MHeironimus/ArduinoJoystickLibrary
 *
 */

#ifndef TEENSYDUINO
#include <Joystick.h>  // Use MHeironimus's Joystick library

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
	10, 0,                  // Button Count, Hat Switch Count
	false, false, false,    // No X, Y, or Z axes
	false, false, false,    // No Rx, Ry, or Rz
	false, false,           // No rudder or throttle
	false, false, false);   // No accelerator, brake, or steering

const uint8_t ButtonOffset = 1; // Arduino Joystick buttons are indexed at 0
#else
const uint8_t ButtonOffset = 0;  // Teensy Joystick buttons are indexed at 1
#endif

#include <HID_Buttons.h>  // Must import AFTER Joystick.h

const uint8_t ButtonPin = 6;  // Pin for hardware button
const uint8_t ButtonNumber = 1 - ButtonOffset;  // Press this Joystick button # when the pin is grounded

JoystickButton myButton(ButtonNumber);

void setup() {
	pinMode(ButtonPin, INPUT_PULLUP);
	Joystick.begin();
}

void loop() {
	boolean pressed = !digitalRead(ButtonPin);
	myButton.set(pressed);
}
