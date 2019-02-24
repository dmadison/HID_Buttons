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
 */

#ifndef HID_Button_Joystick_h
#define HID_Button_Joystick_h

#include "HID_Button_API.h"

 /*
  * Include Guard Info
  * --------------------
  *
  * Arduino Boards:
  *     JOYSTICK_h   MHeironimus header include guard (pluggable HID)
  *     USB_CON      defined by the architecture if USB support exists
  *
  * Teensy:
  *     TEENSYDUINO             defined if using any Teensy board
  *     USB_HID                 defined by boards.txt if using USB type "Keyboard + Mouse + Joystick"
  *     USB_SERIAL_HID          defined by boards.txt if using USB type "Serial + Keyboard + Mouse + Joystick"
  *     USB_FLIGHTSIM_JOYSTICK  defined by boards.txt if using USB type "Flight Sim Controls + Joystick"
  */

#if (defined(JOYSTICK_h) && defined(USBCON)) || \
	(defined(TEENSYDUINO) && \
	(defined(USB_HID) || defined(USB_SERIAL_HID) || defined(USB_FLIGHTSIM_JOYSTICK)))

#define HID_BUTTON_JOYSTICK

class JoystickButton : public HID_Button {
public:
	JoystickButton(uint8_t b) :
		buttonNumber(b) {}

	static void releaseAll() {
		HID_Button::releaseAll(HID_Button_Type::Joystick);
	}

	uint16_t getButton() const {
		return buttonNumber;
	}

	HID_Button_Type getType() const {
		return HID_Button_Type::Joystick;
	}

protected:
	void sendState(boolean state) {
		#if defined(JOYSTICK_h)  // MHeironimus library
			extern Joystick_ Joystick;  // Using the expected name for the object
			Joystick.setButton(buttonNumber, state);
		#elif defined(TEENSYDUINO)
			Joystick.button(buttonNumber, state);
		#endif
	}

	const uint8_t buttonNumber;
};

#endif

#endif
