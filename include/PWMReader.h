#ifndef PWM_READER_H
#define PWM_READER_H

#include <Arduino.h>
#include "Configuration.h"

class PWMReader {
private:
    uint8_t pin;
    volatile unsigned long pulseStart;
    volatile unsigned long pulseWidth;
    volatile bool newPulse;

public:
    PWMReader(uint8_t inputPin);
    void init();
    unsigned long getPulseWidth();
    bool hasNewPulse();
    void clearNewPulse();
    static void pulseStartInterrupt();
    static void pulseEndInterrupt();
};

#endif