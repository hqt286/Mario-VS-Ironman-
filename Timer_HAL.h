//------------------------------------------
// TIMER API
// Also known as TIMER HAL (Hardware Abstraction Layer)
// HAL is a specific form of API that designs the interface with a certain hardware

#ifndef TIMERS_H_
#define TIMERS_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>


typedef struct {
    uint32_t    hwtimer;        // hardware timer used as basis for this software timer
    uint32_t    waitCycles;     // wait "cycles" for the software timer
    uint32_t    startCounter;   // last counter value when the SW timer started (C1)
} OneShotSWTimer_t;

typedef struct {
    uint32_t    hwtimer50;        // hardware timer used as basis for this software timer
    uint32_t    waitCycles50;     // wait "cycles" for the software timer
    uint32_t    startCounter50;   // last counter value when the SW timer started (C1)
} OneShot50msTimer;

typedef struct {
    uint32_t    hwtimer30;        // hardware timer used as basis for this software timer
    uint32_t    waitCycles30;     // wait "cycles" for the software timer
    uint32_t    startCounter30;   // last counter value when the SW timer started (C1)
} OneShotEnemyTimer;
/*
 * This function ties the software period pointed by OST to hwtimer and sets its wait cycles
 */
void InitOneShotSWTimer(OneShotSWTimer_t* OST,
                        uint32_t  hwtimer,
                        uint32_t  waitCycles);

void InitOneShot50msTimer(
        OneShot50msTimer* OST50,
        uint32_t  hwtimer,
        uint32_t  TimeInMS);

void InitOneShotEnemyTimer(OneShotEnemyTimer* OST30,
                        uint32_t  hwtimer,
                        uint32_t  waitCycles);
/*
 * This function simply records the start time which is C1 from notes
 */
void StartOneShotSWTimer(OneShotSWTimer_t* OST);

void StartOneShot50Timer(OneShot50msTimer* OST50);

void StartOneShotEnemyTimer(OneShotEnemyTimer* OST30);
/*
 * This function checks to see if the sw timer has expired, i.e. wait cycles has passed
 */
bool OneShotSWTimerExpired(OneShotSWTimer_t* OST);

bool OneShot50TimerExpired(OneShot50msTimer* OST50);

bool OneShotEnemyTimerExpired(OneShotEnemyTimer* OST30);
/*
 * This function initializes both hw timers
 */
void InitHWTimers();



#endif // TIMERS_H_
