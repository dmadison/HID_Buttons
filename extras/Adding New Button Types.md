# Adding New HID Button Types

Adding a new HID button type to the library is a piece of cake. You will need to build a new header with a custom class that defines how to interface with that HID type.

To demonstrate I'm going to be using the [Mouse button](../src/variants/HID_Button_Mouse.h) as an example.

## Setup

To start, create a new header file in the `src/variants` folder called `HID_Button_Type.h`, where 'Type' is the name of your new HID type. In this file, include a header guard and import the button API:

```cpp
#ifndef HID_Button_Mouse_h
#define HID_Button_Mouse_h

#include "HID_Button_API.h"
...
#endif
```

Next, add some guards so that the button class is only defined when the relevant HID mode is present. For the "pluggable" Arduino HID modes it's enough to use the include guards from the relevant library. With the built-in Mouse library this is the `MOUSE_h` guard and the Arduino's `_USING_HID` flag from the core:

```cpp
#if defined(MOUSE_h) && defined(_USING_HID)
...
#endif
```

Immediately after this you should define your own flag for the HID type. This is so that the user can easily test whether the button type exists in their own code:

```cpp
#define HID_BUTTON_MOUSE
```

Inside of this `#if` block is the button class definition. Start by importing the base class, `HID_Button`, using public inheritance:

```cpp
class MouseButton : public HID_Button {
...
}
```

You'll probably also want to define a constructor to store whatever the button reference value is. For a Keyboard this is what key to press, for a Mouse it's what mouse button to press, etc.

```cpp
public:
	MouseButton(uint8_t b) :
		buttonID(b) {}
	...
protected:
	const uint8_t buttonID;
```

What type(s) to use and how this is assigned is left to you. You can also omit a constructor altogether if your HID mode works differently.

## Specialization

The base class will take care of almost everything. To specialize it to your HID mode, you need to define a few functions:

```cpp
public:
	void releaseAll();
	uint16_t getButton() const;
	HID_Button_Type getType() const;

protected:
	void sendState(boolean state);
```

The main one here is `sendState`, which takes a boolean argument for the current state of the button and sends the state to whatever HID device it's using:

```cpp
	void sendState(boolean state) {
		state ? Mouse.press(buttonID) : Mouse.release(buttonID);
	}
```

There are two 'get' functions that return information from the class: `getButton` which returns the button ID mentioned above (Keyboard key, Mouse button number, etc.), and `getType` which returns the HID type for the class. These `HID_Button_Type`s are defined in a classed enum in [`HID_Button_API.h`](../src/HID_Button_API.h). If one of the available ones does not fit your HID type, you will need to add it to the enum.

```cpp
public:
	uint16_t getButton() const {
		return buttonID;
	}

	HID_Button_Type getType() const {
		return HID_Button_Type::Mouse;
	}
```

Last but not least, you need to add a static `releaseAll` function that is specific to your HID type. This uses the virtual `getType` functions to parse through the linked list of buttons and release only those that match that specific type:

```cpp
public:
	static void releaseAll() {
		HID_Button::releaseAll(HID_Button_Type::Mouse);
	}
```

## Wrapping Up

With that your class should be fully defined! There are just a few things left to do in order to integrate it into the library:

### Include with Library

Your variant is defined but isn't included with the rest of the library (yet). Edit the [`HID_Buttons.h` file](../src/HID_Buttons.h) to `#include` your variant so it's imported into the sketch.

### Define Keywords

Modify the [`keywords.txt`](../keywords.txt) file and add your HID type under the "Variant Classes" list in the first section ("Datatypes (KEYWORD1)"). You *must* use a single tab between your class name and the keyword "KEYWORD1".

### Build an Example

Lastly, build at least one example of your HID mode working and put it into the [`examples`](../examples) directory under a subfolder for the HID type. Follow the [Arduino example style guide](https://www.arduino.cc/en/Reference/StyleGuide) as best you can, and prefer things being easy to understand over brevity.

---
And you're done!
