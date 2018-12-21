//------------------------------------------
// BUTTON API API (Application Programming Interface)
// Also known as BUTTON HAL (Hardware Abstraction Layer)
// HAL is a specific form of API that designs the interface with a certain hardware

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void InitButtons();

// The below functions return true if the button mentioned in the function name is pressed
// These functions use raw button status
bool Booster_Top_Button_Pressed();
bool Booster_Bottom_Button_Pressed();
bool Launchpad_Left_Button_Pressed();
bool Launchpad_Right_Button_Pressed();
bool Joystick_Button_Pressed();

// The below functions return true if the button mentioned in the function name is pushed
// Pushing means pressing followed by releasing. The function returns true as soon as the button is released.
// These functions use debounced button status
bool Booster_Top_Button_Pushed();
bool Booster_Bottom_Button_Pushed();
bool JoyStick_Button_Pushed();
#endif // BUTTONS_H_
