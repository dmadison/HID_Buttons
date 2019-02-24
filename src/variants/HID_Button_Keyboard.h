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

#ifndef HID_Button_Keyboard_h
#define HID_Button_Keyboard_h

#include "HID_Button_API.h"

 /*
  * Include Guard Info
  * --------------------
  *
  * Arduino Boards:
  *     KEYBOARD_h   built-in library header include guard
  *     _USING_HID   defined in HID.h if USB is enabled (USBCON)
  *
  * Teensy:
  *     TEENSYDUINO       defined if using any Teensy board
  *     USB_KEYBOARDONLY  defined by boards.txt if using USB type "Keyboard"
  *     USB_HID           defined by boards.txt if using USB type "Keyboard + Mouse + Joystick"
  *     USB_SERIAL_HID    defined by boards.txt if using USB type "Serial + Keyboard + Mouse + Joystick"
  *     USB_TOUCHSCREEN      defined by boards.txt if using USB type "Keyboard + Touch Screen"
  *     USB_HID_TOUCHSCREEN  defined by boards.txt if using USB type "Keyboard + Mouse + Touch Screen"
  */

#if (defined(KEYBOARD_h) && defined(_USING_HID)) || \
	(defined(TEENSYDUINO) && \
	(defined(USB_KEYBOARDONLY) || defined(USB_HID) || defined(USB_SERIAL_HID) \
	 || defined(USB_TOUCHSCREEN) || defined(USB_HID_TOUCHSCREEN)))

#define HID_BUTTON_KEYBOARD

class KeyboardButton : public HID_Button {
public:

#ifdef TEENSYDUINO
	using KeySize = uint16_t;
#else
	using KeySize = uint8_t;
#endif

	KeyboardButton(KeySize k) :
		key(k) {}

	static void releaseAll() {
		HID_Button::releaseAll(HID_Button_Type::Keyboard);
	}

	uint16_t getButton() const {
		return key;
	}

	HID_Button_Type getType() const {
		return HID_Button_Type::Keyboard;
	}

protected:
	void sendState(boolean state) {
		state ? Keyboard.press(key) : Keyboard.release(key);
	}

	const KeySize key;
};
#endif

#endif
