#include "Drum.h"

// Hardware pins
#define STEP_PIN 9
#define DIR_PIN 8
#define EN_PIN 7
#define STICK_A 20
#define STICK_B 21

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
    stepper.setAcceleration(MAX_ACCELERATION);
    // Enable motor
    digitalWrite(EN_PIN, LOW); //need to disable it later (positioning may drift)
    // Calculate minMoveTime based on max acceleration
    // We always start from rest and accelreate for half the distance, then decelerate
    // t = sqrt(2(s/2)/a) * 2 = 2*sqrt(s/a)
    // We also always want the movement to take the same time regardless of distance
    // So our minMoveTime is based on the max distance (4 notes = 800 steps)
    minMoveTime = 2.0 * sqrt( 800 / MAX_ACCELERATION );
    // for a MAX_ACCELERATION of 45000, minMoveTime = 0.266s
}

void Drum::moveToPosition(int targetDrumPosition) {
    // Move the drum to the specified position in a blocking manner
    int posToMove = (targetDrumPosition - currentDrumPosition + 8) % 8;
    if (posToMove > 4) posToMove -= 8; // Choose shortest path
    int stepsToMove = posToMove * STEPS_PER_NOTE;

    // Base case, no movement needed
    if (stepsToMove == 0) {
        delay(minMoveTime * 1000); // Delay minMoveTime to keep timing consistent
        return;
    }

    // Max speed isn't relevant since we are acceleration-limited
    // Set it to a high value to avoid limiting the motion
    stepper.setMaxSpeed(MAX_RPM * STEPS_PER_REV / 60.0);

    // Calculate required acceleration to complete move in minMoveTime
    // a = 4s/t^2
    float requiredAcceleration = (4.0 * abs(stepsToMove)) / (minMoveTime * minMoveTime);

    stepper.setAcceleration(requiredAcceleration);
    long targetSteps = stepper.currentPosition() + stepsToMove;
    stepper.moveTo(targetSteps);

    while (stepper.distanceToGo() != 0) {
        stepper.run();
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
const float Drum::MAX_RPM = 3000.0f; // irrelevant (acceleration-limited)
const float Drum::MAX_ACCELERATION = 45000.0f; // steps/sec^2 - Measured to be between 40,000 and 48,000
