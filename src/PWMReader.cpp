#include "PWMReader.h"

volatile unsigned long pulseStartTime = 0;
volatile unsigned long* currentPulseWidth = nullptr;
volatile bool* currentNewPulse = nullptr;

PWMReader::PWMReader(uint8_t inputPin) : pin(inputPin) {
    pulseStart = 0;
    pulseWidth = 0;
    newPulse = false;
}

void PWMReader::init() {
    pinMode(pin, INPUT);
    currentPulseWidth = &pulseWidth;
    currentNewPulse = &newPulse;
    attachInterrupt(digitalPinToInterrupt(pin), pulseStartInterrupt, RISING);
}

void PWMReader::pulseStartInterrupt() {
    pulseStartTime = micros();
    attachInterrupt(digitalPinToInterrupt(PWM_INPUT_PIN), PWMReader::pulseEndInterrupt, FALLING);
}

void PWMReader::pulseEndInterrupt() {
    if (currentPulseWidth && currentNewPulse) {
        *currentPulseWidth = micros() - pulseStartTime;
        *currentNewPulse = true;
    }
    attachInterrupt(digitalPinToInterrupt(PWM_INPUT_PIN), PWMReader::pulseStartInterrupt, RISING);
}

unsigned long PWMReader::getPulseWidth() {
    return pulseWidth;
}

bool PWMReader::hasNewPulse() {
    return newPulse;
}

void PWMReader::clearNewPulse() {
    newPulse = false;
}
