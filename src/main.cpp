#include <Arduino.h>
#include "Configuration.h"
#include "MotorController.h"
#include "PWMReader.h"

MotorController motor1(MOTOR1_STEP_PIN, MOTOR1_DIR_PIN, MOTOR1_ENABLE_PIN);
MotorController motor2(MOTOR2_STEP_PIN, MOTOR2_DIR_PIN, MOTOR2_ENABLE_PIN);
PWMReader pwmReader(PWM_INPUT_PIN);

long currentPosition = 0;
long targetPosition = 0;
bool isMoving = false;

// Debug variables
unsigned long lastDebugTime = 0;
char debugBuffer[100];  // Buffer for building debug strings

void printDebugInfo(unsigned long pwmValue) {
    if (millis() - lastDebugTime >= DEBUG_INTERVAL) {
        // Clear buffer
        memset(debugBuffer, 0, sizeof(debugBuffer));
        
        // Build status string
        snprintf(debugBuffer, sizeof(debugBuffer), 
                "PWM:%lu,Pos:%ld,Target:%ld,Moving:%d\n",
                pwmValue, currentPosition, targetPosition, isMoving);
        
        // Print debug info
        Serial.print(debugBuffer);
        
        lastDebugTime = millis();
    }
}

void handlePWMInput(unsigned long pwmValue) {
    long maxSteps = (TOTAL_TRAVEL / LEAD_SCREW_PITCH) * STEPS_PER_REVOLUTION * MICROSTEPS;
    
    if (abs((long)pwmValue - PWM_RETRACT_VALUE) <= PWM_TOLERANCE) {
        targetPosition = 0;
        if (!isMoving && currentPosition > 0) {
            motor1.enable();
            motor2.enable();
            isMoving = true;
        }
    }
    else if (abs((long)pwmValue - PWM_EXTEND_VALUE) <= PWM_TOLERANCE) {
        targetPosition = maxSteps;
        if (!isMoving && currentPosition < maxSteps) {
            motor1.enable();
            motor2.enable();
            isMoving = true;
        }
    }
    
    // Print debug info
    printDebugInfo(pwmValue);
}

void setup() {
    // Initialize serial with proper baud rate
    Serial.begin(DEBUG_BAUD_RATE);
    
    // Wait for serial to be ready
    while (!Serial) {
        delay(10);
    }
    
    motor1.init();
    motor2.init();
    pwmReader.init();
    
    // Print startup message
    Serial.println(F("Camera Retraction System Started"));
    Serial.println(F("Format: PWM,Position,Target,Moving"));
}

void loop() {
    static unsigned long lastPWMValue = 0;
    
    if (pwmReader.hasNewPulse()) {
        lastPWMValue = pwmReader.getPulseWidth();
        pwmReader.clearNewPulse();
        handlePWMInput(lastPWMValue);
    }

    if (isMoving) {
        unsigned long stepDelay = 1000000 / MAX_SPEED;
        bool direction = currentPosition < targetPosition;
        
        if (direction && currentPosition < targetPosition) {
            if (motor1.move(direction, stepDelay)) {
                motor2.move(direction, stepDelay);
                currentPosition++;
            }
        }
        else if (!direction && currentPosition > targetPosition) {
            if (motor1.move(direction, stepDelay)) {
                motor2.move(direction, stepDelay);
                currentPosition--;
            }
        }
        else {
            isMoving = false;
            motor1.disable();
            motor2.disable();
            
            // Print status when movement stops
            snprintf(debugBuffer, sizeof(debugBuffer), 
                    "Movement Complete. Final Position: %ld\n", 
                    currentPosition);
            Serial.print(debugBuffer);
        }
    }
    
    // Regular status updates even when not moving
    printDebugInfo(lastPWMValue);
    Serial.print(micros());
}