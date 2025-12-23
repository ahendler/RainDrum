#include "Drum.h"

// Hardware pins
#define STEP_PIN 22
#define DIR_PIN 23
#define EN_PIN 19
#define STICK_A 18
#define STICK_B 17


Drum::Drum() : stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN) {}

void Drum::initialize() {
    pinMode(EN_PIN, OUTPUT);
    digitalWrite(EN_PIN, HIGH); // Disable motor initially
    pinMode(STICK_A, OUTPUT);
    digitalWrite(STICK_A, HIGH);
    pinMode(STICK_B, OUTPUT);
    digitalWrite(STICK_B, HIGH);
    // Configure stepper
    float maxSpeedSteps = (STEPS_PER_REV * MAX_RPM) / 60.0;
    stepper.setMaxSpeed(maxSpeedSteps);
    stepper.setAcceleration(maxSpeedSteps * 2);
    // Enable motor
    digitalWrite(EN_PIN, LOW); //need to disable it later (positioning may drift)
}

void Drum::moveToPosition(int targetDrumPosition) {
    // Move the drum to the specified position in a blocking manner
    int posToMove = (targetDrumPosition - currentDrumPosition + 8) % 8;
    if (posToMove > 4) posToMove -= 8; // Choose shortest path
    int stepsToMove = posToMove * STEPS_PER_NOTE;


    if (stepsToMove != 0) {
        // Speed based on fixed time for movement for now
        float requiredSpeed = abs(stepsToMove) / 0.2; // Move in 0.2 second
        // float maxSpeedSteps = (STEPS_PER_REV * MAX_RPM) / 60.0;
        // requiredSpeed = (requiredSpeed > maxSpeedSteps) ? maxSpeedSteps : requiredSpeed;

        stepper.setMaxSpeed(requiredSpeed);
        // Use speed value x5 for acceleration, tune needed
        stepper.setAcceleration(MAX_ACCELERATION);
        long targetSteps = stepper.currentPosition() + stepsToMove;
        stepper.moveTo(targetSteps);

        while (stepper.distanceToGo() != 0) {
            stepper.run();
        }
    } else {
        // Delay 200 ms to simulate the time taken for a movement
        delay(200);
    }
    currentDrumPosition = targetDrumPosition; 
}

void Drum::strike() {
    digitalWrite(STICK_A, LOW);
    delay(20); // Strike duration
    digitalWrite(STICK_A, HIGH);
}

void Drum::moveToPositionAndStrike(int position) {
    moveToPosition(position);
    strike();
    Serial.println("Struck position " + String(position));
}

const int Drum::STEPS_PER_REV = 1600;
const int Drum::STEPS_PER_NOTE = 200;
const float Drum::MAX_RPM = 1500.0f; // irrelevant (acceleration-limited)
const float Drum::MAX_ACCELERATION = 38000.0f; // steps/sec^2 - Measured to be between 40,000 and 48,000
