#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void initADC_Multi() {
    ADC14_enableModule();

    // This sets the conversion clock to 3MHz
    ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC,
                     ADC_PREDIVIDER_1,
                     ADC_DIVIDER_1,
                      0
                     );

    ADC14_setResolution(ADC_14BIT);

    // This configures the ADC to store output results
    // in ADC_MEM0 up to ADC_MEM1. Each conversion will
    // thus use two channels.
    ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);

    // This configures the ADC in manual conversion mode
    // Software will start each conversion.
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
}
void initADC_Single() {
    ADC14_enableModule();

    // This sets the conversion clock to 3MHz
    ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC,
                     ADC_PREDIVIDER_1,
                     ADC_DIVIDER_1,
                      0
                     );

    ADC14_setResolution(ADC_14BIT);

    // This configures the ADC to store output results
    // in ADC_MEM0 (single-channel conversion, repeat mode)
    ADC14_configureSingleSampleMode(ADC_MEM0, true);

    // This configures the ADC in automatic conversion mode
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
}

void startADC() {
    // The ADC is in continuous sampling mode, so after calling this once
    // the ADC will continuously update
    ADC14_enableConversion();
    ADC14_toggleConversionTrigger();
}


void initMicrophone() {
    // This configures ADC_MEM0 to store the result from
    // input channel A10 (Microphone), in non-differential input mode
    // (non-differential means: only a single input pin)
    // The reference for Vref- and Vref+ are VSS and VCC respectively
    ADC14_configureConversionMemory(ADC_MEM0,
                                    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    ADC_INPUT_A10,
                                    ADC_NONDIFFERENTIAL_INPUTS);

    // This selects the GPIO as analog input
    // A9 is multiplexed on GPIO port P4 pin PIN4
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,
                                               GPIO_PIN3,
                                               GPIO_TERTIARY_MODULE_FUNCTION);
}

unsigned getSampleMicrophone() {
    return ADC14_getResult(ADC_MEM0);
}


unsigned sampleconv(unsigned v) {
    // This function maps on ADC sample (range 0 to 3FFF, midpoint 1FFF)
    // to the display Y coordinates (range 0 to 127, midpoint 64)
    // It also adds a digital gain factor
    int s0127 = (0x3FFF - v) / 128; // scaled 0 to 127, midpoint 64
    int gain = 4;
    return (unsigned) (s0127 - 64) * gain + 64;
}



void initJoyStick() {

    // This configures ADC_MEM0 to store the result from
    // input channel A15 (Joystick X), in non-differential input mode
    // (non-differential means: only a single input pin)
    // The reference for Vref- and Vref+ are VSS and VCC respectively
    ADC14_configureConversionMemory(ADC_MEM0,
                                  ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                  ADC_INPUT_A15,                 // joystick X
                                  ADC_NONDIFFERENTIAL_INPUTS);

    // This selects the GPIO as analog input
    // A15 is multiplexed on GPIO port P6 pin PIN0
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
                                               GPIO_PIN0,
                                               GPIO_PRIMARY_MODULE_FUNCTION);

    // This configures ADC_MEM0 to store the result from
    // input channel A15 (Joystick X), in non-differential input mode
    // (non-differential means: only a single input pin)
    // The reference for Vref- and Vref+ are VSS and VCC respectively
    ADC14_configureConversionMemory(ADC_MEM1,
                                    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    ADC_INPUT_A9,                 // joystick Y
                                    ADC_NONDIFFERENTIAL_INPUTS);

    // This selects the GPIO as analog input
    // A9 is multiplexed on GPIO port P4 pin PIN4
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,
                                               GPIO_PIN4,
                                               GPIO_TERTIARY_MODULE_FUNCTION);
}

void getSampleJoyStick(unsigned *X, unsigned *Y) {
    // ADC runs in continuous mode, we just read the conversion buffers
    *X = ADC14_getResult(ADC_MEM0);
    *Y = ADC14_getResult(ADC_MEM1);
}
