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

#ifndef HID_Button_API_h
#define HID_Button_API_h

#include <Arduino.h>

enum class HID_Button_Type {
	// Variants
	Keyboard,
	Mouse,
	Joystick,
	Custom,

	// Meta Options
	All,
	None,
};

class HID_Button {
public:
	HID_Button();
	~HID_Button();

	static void releaseAll();

	void press();
	void release();

	void toggle();
	void write();  // Press and release

	void set(boolean state);

	boolean isPressed() const;
	virtual uint16_t getButton() const = 0;
	virtual HID_Button_Type getType() const = 0;

protected:
	static void releaseAll(HID_Button_Type limitTo);
	virtual void sendState(boolean state) = 0;

	boolean pressed = false;

private:
	static HID_Button * head;
	static HID_Button * tail;

	HID_Button * next = nullptr;
};

#endif
