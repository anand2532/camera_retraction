#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>
#include "Configuration.h"

class MotorController {
private:
    uint8_t stepPin;
    uint8_t dirPin;
    uint8_t enablePin;
    unsigned long lastStepTime;

public:
    MotorController(uint8_t step_pin, uint8_t dir_pin, uint8_t enable_pin);
    void init();
    void enable();
    void disable();
    void setDirection(bool direction);
    void step();
    bool move(bool direction, unsigned long stepDelay);
};

#endif
