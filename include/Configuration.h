#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <Arduino.h>

// Debug Settings
#define DEBUG_BAUD_RATE 9600    // Changed to more stable baud rate
#define DEBUG_INTERVAL 500      // Debug print interval in milliseconds

// Pin definitions for Motor 1
const uint8_t MOTOR1_STEP_PIN = 2;
const uint8_t MOTOR1_DIR_PIN = 3;
const uint8_t MOTOR1_ENABLE_PIN = 4;

// Pin definitions for Motor 2
const uint8_t MOTOR2_STEP_PIN = 5;
const uint8_t MOTOR2_DIR_PIN = 6;
const uint8_t MOTOR2_ENABLE_PIN = 7;

// PWM Input Pin
const uint8_t PWM_INPUT_PIN = 8;

// Movement parameters
const uint16_t STEPS_PER_REVOLUTION = 200;    // For NEMA8 20HS24
const uint8_t MICROSTEPS = 16;                // A4988 microstepping setting
const float LEAD_SCREW_PITCH = 2.0;           // mm per revolution
const uint16_t MAX_SPEED = 1000;              // Maximum speed in steps per second
const uint16_t ACCELERATION = 500;            // Steps per second per second
const uint8_t TOTAL_TRAVEL = 100;             // Total travel distance in mm

// PWM Signal Parameters
const uint16_t PWM_RETRACT_VALUE = 1000;      // Target PWM value for retraction
const uint16_t PWM_EXTEND_VALUE = 2000;       // Target PWM value for extension
const uint8_t PWM_TOLERANCE = 10;             // Tolerance range for PWM values
const uint16_t PWM_TIMEOUT = 25000;           // Timeout for PWM signal in microseconds

#endif