#include <AccelStepper.h>

// Hardware pins
#define STEP_PIN 9
#define DIR_PIN 8
#define EN_PIN 7

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
// Motor constants
const int STEPS_PER_REV = 1600;
const int half_rev = 800;

// Test Parameters
float current_acceleration = 40000.0f;
float max_test_acceleration = 66000.0f;
float acceleration_increment = 1000.0f;
// Set a high speed limit so we are limited by acceleration, not top speed setting
float speed_limit_for_test = 500000.0f; 

void setup() {

  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW); // Enable motor (Active LOW)

  // Set the speed limit once, high enough to not be the bottleneck
  stepper.setMaxSpeed(speed_limit_for_test);
  
  delay(3000);
}

void loop() {
  if (current_acceleration <= max_test_acceleration) {
    
    stepper.setAcceleration(current_acceleration);

    // Perform 8 repetitions for the current acceleration
    for(int i = 0; i < 8; i++) {
      stepper.move(half_rev);
      while (stepper.distanceToGo() != 0) {
        stepper.run();
      }
      delay(100);
    }
    
    // 1 second break between accel values for easier manual accounting
    delay(1000);

    current_acceleration += acceleration_increment; 
  } else {
    // disable motor and stop test
    digitalWrite(EN_PIN, HIGH); 
    while (true);
  }
}