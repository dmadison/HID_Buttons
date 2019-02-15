# HID Buttons Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/HID%20Buttons.svg?)](https://www.ardu-badge.com/HID%20Buttons) [![Build Status](https://travis-ci.org/dmadison/HID_Buttons.svg?branch=master)](https://travis-ci.org/dmadison/HID_Buttons)

This small Arduino library makes it easier to set up programs that use Keyboard, Mouse, or Joystick buttons by storing the associated key / button ID and output state for comparison. This makes your code cleaner, simpler, and prevents spamming USB reports with duplicated keypresses.

#### Before:

```cpp
	if (stickY < -300) {
		if (aPressed == 0){
			aPressed = 1;
			Keyboard.press('a');
		}
	}
	else {
		if (aPressed == 1) {
			aPressed = 0;
			Keyboard.release('a');
		}
	}
```

#### After:

```cpp
	KeyboardButton ButtonA('a');
	...
	ButtonA.set(stickY < -300);
```

All HID button types share a common base class and are treated identically, allowing you to share logic between buttons on composite devices (e.g. Keyboard + Mouse).

## Button 'Set' Functions
```cpp
void press();
void release();

void toggle();
void write();

void set(boolean state);

static void releaseAll();
```

### Press / Release

The traditional `press()` and `release()` functions are present and accounted for! These pass through the class's state filter so repeated calls will avoid spamming USB messages.

### Set

This is `press()` and `release()` wrapped up into one convenient function. Pass a boolean to `set()` the state of the button. True is 'pressed', false is 'released'.

### Toggle

Flip it! Calling `toggle()` changes a press to a release and a release to a press.

### Write

Don't need to hold it down? Call `write()` to press and release a button right away.

### ReleaseAll

Release all of the buttons! Can be called either on the base class to release everything:
```cpp
HID_Button::releaseAll();
```
Or on a specific type to release only buttons of that type:
```cpp
KeyboardButton::releaseAll();  // release Keyboard buttons only
MouseButton::releaseAll();  // release Mouse buttons only
...
```
## Button 'Get' Functions
```cpp
boolean isPressed() const;
virtual uint16_t getButton() const;
virtual HID_Button_Type getType() const;
```

### IsPressed

Calling `getPressed()` will return the internal button state, where 'true' is pressed and 'false' is released.

### GetButton

Calling `getButton()` will return the key or button identifier for that object. For a `KeyboardButton` this is the key, for a `MouseButton` or `JoystickButton` this is the button number.

### GetType

The `getType()` function will return the HID type for that specific button object using the library's classed enumeration. If you're passing objects using the base class (`HID_Button`) this will tell you what HID type that button is using.

## Supported HID Types
The library currently supports three HID button types:
* [Keyboard](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/)
* [Mouse](https://www.arduino.cc/reference/en/language/functions/usb/mouse/)
* [Joystick](https://github.com/MHeironimus/ArduinoJoystickLibrary)

All three of these HID types are also supported on the Teensy using its native libraries.

To add support for a new HID type, please see [the documentation in the 'extras' folder](extras/Adding%20New%20Button%20Types.md).

## License
Released under the terms of the permissive [MIT license](https://opensource.org/licenses/MIT). See the [LICENSE](LICENSE) file for more information.
