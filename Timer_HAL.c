//------------------------------------------
// Timer API (Application Programming Interface)
// Also known as BUTTON HAL (Hardware Abstraction Layer)
// HAL is a specific form of API that designs the interface with a certain hardware

#include <TIMER_HAL.h>

#define TIMER0_PRESCALER TIMER32_PRESCALER_1
#define TIMER1_PRESCALER TIMER32_PRESCALER_256
#define SYS_CLOCK_F 48000000

/* This function gets the hardware timer (since it needs its prescaler value) and time in milliseconds
 * and returns the number of wait cycles associated with that time.
 * For example, if the system clock is 3 MHz, the prescaler is 1 and TimeInMS is 1000, then the
 * returned value is going to be 3000,000
 * If the number of wait cycles is too big for this software timer to be used, it returns -1
 */
int64_t WaitCycles(uint32_t hwtimer, uint64_t TimeInMS)
{
     // This function returns the system clock
    //uint64_t sysClock = CS_getSMCLK();
    uint64_t sysClock = SYS_CLOCK_F;

    uint8_t  prescalerFlag;
    uint64_t prescalerValue;

    // Based on the hw timer, we have to see which prescaler to use
    if (hwtimer == TIMER32_0_BASE)
        prescalerFlag = TIMER0_PRESCALER;
    else if (hwtimer == TIMER32_1_BASE)
        prescalerFlag = TIMER1_PRESCALER;

    // The prescaler we get in the previous section is simply a flag. "Control click" on it to see what I mean.
    // We need to turn that into the actual value of the prescaler
    switch(prescalerFlag)
    {
    case TIMER32_PRESCALER_1:
        prescalerValue = 1;
        break;
    case TIMER32_PRESCALER_16:
        prescalerValue = 16;
        break;
    case TIMER32_PRESCALER_256:
        prescalerValue = 256;
        break;
    }

    int64_t waitCycles;
    waitCycles = TimeInMS * (sysClock / prescalerValue / 1000);

    if (waitCycles > UINT32_MAX)
        waitCycles = -1;

    return waitCycles;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                  OneShotSWTimer
bool OneShotSWTimerExpired(OneShotSWTimer_t* OST)
{
    bool expired = false;

    // HW timer period
    int64_t HWTimerPeriod = UINT32_MAX+ 1;

    //This is C2 from notes, while OST->startCounter is C1
    uint32_t currentCounter = Timer32_getValue(OST->hwtimer);

    int64_t ElapsedCycles =  OST->startCounter - currentCounter;
    if (ElapsedCycles < 0)
        ElapsedCycles += HWTimerPeriod ;

    if (ElapsedCycles >= OST->waitCycles)
        expired = true;
    else
        expired = false;

    return expired;
}

void StartOneShotSWTimer(OneShotSWTimer_t* OST)
{
    OST->startCounter = Timer32_getValue(OST->hwtimer);
}



void InitOneShotSWTimer(
        OneShotSWTimer_t* OST,
        uint32_t  hwtimer,
        uint32_t  TimeInMS)
{
    OST->hwtimer = hwtimer;

    OST->waitCycles  = WaitCycles(hwtimer, TimeInMS);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                  OneShot50Timer

void InitOneShot50msTimer(
        OneShot50msTimer* OST50,
        uint32_t  hwtimer,
        uint32_t  TimeInMS)
{
    OST50 ->hwtimer50 = hwtimer;

    OST50 ->waitCycles50  = WaitCycles(hwtimer, TimeInMS);
}

void StartOneShot50Timer(OneShot50msTimer* OST50)
{
    OST50->startCounter50 = Timer32_getValue(OST50->hwtimer50);
}

bool OneShot50TimerExpired(OneShot50msTimer* OST50)
{
    bool expired = false;

    // HW timer period
    int64_t HWTimerPeriod = UINT32_MAX+ 1;

    //This is C2 from notes, while OST->startCounter is C1
    uint32_t currentCounter = Timer32_getValue(OST50->hwtimer50);

    int64_t ElapsedCycles =  OST50->startCounter50 - currentCounter;
    if (ElapsedCycles < 0)
        ElapsedCycles += HWTimerPeriod ;

    if (ElapsedCycles >= OST50->waitCycles50)
        expired = true;
    else
        expired = false;

    return expired;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                  OneShot30Timer

void InitOneShotEnemyTimer(
        OneShotEnemyTimer* OST30,
        uint32_t  hwtimer,
        uint32_t  TimeInMS)
{
    OST30 ->hwtimer30 = hwtimer;

    OST30 ->waitCycles30  = WaitCycles(hwtimer, TimeInMS);
}

void StartOneShotEnemyTimer(OneShotEnemyTimer* OST30)
{
    OST30->startCounter30 = Timer32_getValue(OST30->hwtimer30);
}

bool OneShotEnemyTimerExpired(OneShotEnemyTimer* OST30)
{
    bool expired = false;

    // HW timer period
    int64_t HWTimerPeriod = UINT32_MAX+ 1;

    //This is C2 from notes, while OST->startCounter is C1
    uint32_t currentCounter = Timer32_getValue(OST30->hwtimer30);

    int64_t ElapsedCycles =  OST30->startCounter30 - currentCounter;
    if (ElapsedCycles < 0)
        ElapsedCycles += HWTimerPeriod ;

    if (ElapsedCycles >= OST30->waitCycles30)
        expired = true;
    else
        expired = false;

    return expired;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                  Initial Hardware timer


void InitHWTimers() {
    // The prescaler for each of the timers is defined as a macro
    Timer32_initModule(TIMER32_0_BASE, TIMER0_PRESCALER, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    Timer32_setCount(TIMER32_0_BASE, UINT32_MAX);
    Timer32_startTimer(TIMER32_0_BASE, false);

    Timer32_initModule(TIMER32_1_BASE, TIMER1_PRESCALER, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    Timer32_setCount(TIMER32_1_BASE, UINT32_MAX);
    Timer32_startTimer(TIMER32_1_BASE, false);
}




