#include "MotorController.h"

MotorController::MotorController(uint8_t step_pin, uint8_t dir_pin, uint8_t enable_pin) {
    stepPin = step_pin;
    dirPin = dir_pin;
    enablePin = enable_pin;
    lastStepTime = 0;
}

void MotorController::init() {
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    disable();
}

void MotorController::enable() {
    digitalWrite(enablePin, LOW);
}

void MotorController::disable() {
    digitalWrite(enablePin, HIGH);
}

void MotorController::setDirection(bool direction) {
    digitalWrite(dirPin, direction);
}

void MotorController::step() {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(10);
}

bool MotorController::move(bool direction, unsigned long stepDelay) {
    unsigned long currentTime = micros();
    if (currentTime - lastStepTime >= stepDelay) {
        setDirection(direction);
        step();
        lastStepTime = currentTime;
        return true;
    }
    return false;
}