//------------------------------------------
// BUTTON API (Application Programming Interface)
// Also known as BUTTON HAL (Hardware Abstraction Layer)
// HAL is a specific form of API that designs the interface with a certain hardware

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <TIMER_HAL.h>
#include <Buttons_HAL.h>

#define DEBOUNCE_TIMING 100 // 100 ms
typedef enum {stable0, trans0To1, stable1, trans1To0} DebounceState_t;

//------------------------------------------
// Debounce FSM
// This FSM has two inputs the raw button status (rawBtn), which is an input to this funciton
// The other input is the status of the timer that can be directly checked here.
// The FSM also has two outputs. One is the debounced button status (debouncedBtn), which is also the output of this function
// The other output is a boolean that decides whether to start a new timer or not

bool Debounce_Button(DebounceState_t *S, OneShotSWTimer_t *timer, bool rawBtn) {

    // The second input of the FSM
    bool timerExpired = false;

    // Default outputs of the FSM
    bool debouncedBtn = false;
    bool startTimer = false;

    switch (*S)
    {
    case stable0:
        if (rawBtn == 1)
        {
            // Change state
            *S = trans0To1;

            // Update outputs, if different from default
            startTimer = 1;
        }
        break;

    case trans0To1:
        timerExpired = OneShotSWTimerExpired(timer);

        if (timerExpired) {
            if ( rawBtn)
           {
                //Change state
                *S = stable1;

            }
            else
            {
                *S = stable0;
            }
        }
        break;

    case stable1:
        debouncedBtn = 1;
        if (rawBtn == 0) {
            // Change state
            *S = trans1To0;

            // Update outputs, if different from default
            startTimer = 1;
        }
        break;

     case trans1To0:
         timerExpired = OneShotSWTimerExpired(timer);
         debouncedBtn = 1;
         if (rawBtn)
             *S = stable1;
         else
             if (timerExpired)
                 *S = stable0;
        break;
    }

    if (startTimer)
        StartOneShotSWTimer(timer);

    return debouncedBtn;
}



void InitButtons() {
    GPIO_setAsInputPin (GPIO_PORT_P5, GPIO_PIN1); // upper switch S1 on BoostXL

    GPIO_setAsInputPin (GPIO_PORT_P3, GPIO_PIN5); // lower switch S2 on BoostXL

    GPIO_setAsInputPin (GPIO_PORT_P1, GPIO_PIN1); // left button on Launchpad
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);

    GPIO_setAsInputPin (GPIO_PORT_P1, GPIO_PIN4); // right button on Launchpad
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN4);

    GPIO_setAsInputPin (GPIO_PORT_P4, GPIO_PIN1); // Joystick button on Boosterpack
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P4, GPIO_PIN1);
}

bool Joystick_Button_Pressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN1) == 0);
}

bool Booster_Top_Button_Pressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == 0);
}

bool Booster_Bottom_Button_Pressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN5) == 0);
}

bool Launchpad_Left_Button_Pressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == 0);
}

bool Launchpad_Right_Button_Pressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4) == 0);
}

bool Booster_Top_Button_Pushed() {

    static bool prevStatus = false;
    static DebounceState_t debounceState = stable0;
    static OneShotSWTimer_t timer;
    static bool initTimer = false;

    // The timer needs to be initialized only once when the button is used for the first time
    if (!initTimer) {

        InitOneShotSWTimer(&timer,
                           TIMER32_1_BASE,
                           DEBOUNCE_TIMING);
        initTimer = true;
    }

    bool rawStatus = Booster_Top_Button_Pressed();
    bool curStatus = Debounce_Button(&debounceState, &timer, rawStatus);
    bool pushed = (!curStatus && prevStatus);
    prevStatus = curStatus;
    return pushed;
}

bool Booster_Bottom_Button_Pushed() {

    static bool prevStatus = false;
    static DebounceState_t debounceState = stable0;
    static OneShotSWTimer_t timer;
    static bool initTimer = false;

    // The timer needs to be initialized only once when the button is used for the first time
    if (!initTimer) {

        InitOneShotSWTimer(&timer,
                           TIMER32_1_BASE,
                           DEBOUNCE_TIMING);
        initTimer = true;
    }

    bool rawStatus = Booster_Bottom_Button_Pressed();
    bool curStatus = Debounce_Button(&debounceState, &timer, rawStatus);
    bool pushed = (!curStatus && prevStatus);
    prevStatus = curStatus;
    return pushed;
}





bool JoyStick_Button_Pushed() {

    static bool prevStatus = false;
    static DebounceState_t debounceState = stable0;
    static OneShotSWTimer_t timer;
    static bool initTimer = false;

    // The timer needs to be initialized only once when the button is used for the first time
    if (!initTimer) {

        InitOneShotSWTimer(&timer,
                           TIMER32_1_BASE,
                           DEBOUNCE_TIMING);
        initTimer = true;
    }

    bool rawStatus = Joystick_Button_Pressed();
    bool curStatus = Debounce_Button(&debounceState, &timer, rawStatus);
    bool pushed = (!curStatus && prevStatus);
    prevStatus = curStatus;
    return pushed;
}

