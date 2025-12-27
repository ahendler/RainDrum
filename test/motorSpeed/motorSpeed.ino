#include <AccelStepper.h>

// Hardware pins
#define STEP_PIN 9
#define DIR_PIN 8
#define EN_PIN 7

// Motor constants
const int STEPS_PER_REV = 1600;
const int half_rev = 800;
const float MAX_RPM = 5000.0f;

// Calculate max speed in steps/sec
// (1600 steps/rev * 2000 rev/min) / 60 sec/min = 53333.33 steps/sec
const float MAX_SPEED_STEPS = (STEPS_PER_REV * MAX_RPM) / 60.0;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

float currentAcceleration = 20000.0; // Start with a reasonable acceleration
float accelerationIncrement = 5000.0;
float maxTestAcceleration = 60000.0; // Upper limit to stop the test

void setup() {
  Serial.begin(115200);
  while (!Serial);

  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW); // Enable motor (Active LOW)

  stepper.setMaxSpeed(MAX_SPEED_STEPS);
  
  Serial.println("Motor Acceleration Test");
  Serial.println("-----------------------");
  Serial.print("Max Speed: "); Serial.println(MAX_SPEED_STEPS);
  Serial.println("Starting test in 3 seconds...");
  delay(3000);
}

void loop() {
  if (currentAcceleration <= maxTestAcceleration) {
    Serial.print("Testing Acceleration: ");
    Serial.println(currentAcceleration);

    stepper.setAcceleration(currentAcceleration);

    // Move 1 revolution forward
    stepper.move(half_rev);
    while (stepper.distanceToGo() != 0) {
      stepper.run();
    }
    
    delay(200); // Short pause

    // Move 1 revolution backward
    stepper.move(-half_rev);
    while (stepper.distanceToGo() != 0) {
      stepper.run();
    }

    delay(500); // Pause before next iteration

    // Increase acceleration for next run
    currentAcceleration += accelerationIncrement;
  } else {
    Serial.println("Test sequence complete.");
    digitalWrite(EN_PIN, HIGH); // Disable motor
    while(1); // Stop
  }
}
