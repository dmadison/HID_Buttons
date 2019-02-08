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

#include "HID_Button_API.h"

HID_Button * HID_Button::head = nullptr;
HID_Button * HID_Button::tail = nullptr;

HID_Button::HID_Button() {
	// If linked list is empty, set both head and tail
	if (head == nullptr) {
		head = this;
		tail = this;
	}
	// If linked list is *not* empty, set the 'next' ptr of the tail
	// and update the tail
	else {
		tail->next = this;
		tail = this;
	}
}

HID_Button::~HID_Button() {
	// If we're at the start of the list...
	if (this == head) {
		// Option #1: Only element in the list
		if (this == tail) {
			head = nullptr;
			tail = nullptr;  // List is now empty
		}
		// Option #2: First element in the list,
		// but not *only* element
		else {
			head = next;  // Set head to next, and we're done
		}
		return;
	}

	// Option #3: Somewhere else in the list.
	// Iterate through to find it
	HID_Button * ptr = head;

	while (ptr != nullptr) {
		if (ptr->next == this) {  // FOUND!
			ptr->next = next;  // Set the previous "next" as this entry's "next" (skip this object)
			break;  // Stop searching
		}
		ptr = ptr->next;  // Not found. Next entry...
	}

	// Option #4: Last entry in the list
	if (this == tail) {
		tail = ptr;  // Set the tail as the previous entry
	}
}

void HID_Button::releaseAll() {
	releaseAll(HID_Button_Type::All);
}

// Release all buttons, using the linked list
void HID_Button::releaseAll(HID_Button_Type releaseOnly) {
	if (releaseOnly == HID_Button_Type::None) return;

	HID_Button * ptr = head;

	while (ptr != nullptr) {
		// Check if type matches before releasing
		if (releaseOnly == HID_Button_Type::All || releaseOnly == ptr->getType()) {
			ptr->release();
		}
		ptr = ptr->next;
	}
}

void HID_Button::press() {
	set(true);
}

void HID_Button::release() {
	set(false);
}

void HID_Button::set(boolean state) {
	if (state == pressed) {
		return; // Nothing to see here, folks
	}

	sendState(state);
	pressed = state;
}

void HID_Button::toggle() {
	set(!pressed);
}

void HID_Button::write() {
	if (isPressed()) release();
	press();
	release();
}

boolean HID_Button::isPressed() const {
	return pressed;
}
