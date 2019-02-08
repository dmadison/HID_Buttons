# HID Buttons Library

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

All HID button types share a common base class and be treated identically, allowing you to share logic between buttons on composite devices (e.g. Keyboard + Mouse).

## Supported HID Types
The library currently supports three HID button types:
* [Keyboard](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/)
* [Mouse](https://www.arduino.cc/reference/en/language/functions/usb/mouse/)
* [Joystick](https://github.com/MHeironimus/ArduinoJoystickLibrary)

## License
Released under the terms of the permissive [MIT license](https://opensource.org/licenses/MIT). See the [LICENSE](LICENSE) file for more information.
