#define STICK_A 5
#define STICK_B 6

void setup() {
    pinMode(STICK_A, OUTPUT);
    digitalWrite(STICK_A, HIGH);
    
    pinMode(STICK_B, OUTPUT);
    digitalWrite(STICK_B, HIGH);
    Serial.begin(115200);
    Serial.println("Starting Solenoid Speed Test");
}

void loop() {
    //Test how many ms it takes to strike the solenoid
    for (int delayMs = 14; delayMs <= 30; delayMs += 2){
        Serial.println("Striking with delay: " + String(delayMs) + " ms");
        for (int i = 0; i < 6; i++) {
            digitalWrite(STICK_A, LOW);
            delay(delayMs);
            digitalWrite(STICK_A, HIGH);
            delay(500); // Wait .5 second between strikes
        }
        Serial.println("");
        delay(2000); // Wait 2 seconds between different delays
    }
}