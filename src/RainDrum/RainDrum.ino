#include "Drum.h"
#include "MidiBle.h"
#define ARDUINO_USB_CDC_ON_BOOT 1
#define ARDUINO_USB_MODE 1

// MidiBle is only supported on espressif/arduino-esp32 core version 2.0.17 and below

MidiBle midiListener;
Drum drumPlayer;

void setup() {
    Serial.begin(115200);
    drumPlayer.initialize();
    midiListener.initialize();
    Serial.println("Rain Drum Initialized");
}

void loop() {
    midiListener.read();
    if (midiListener.noteToPlay != -1) {
        drumPlayer.moveToPositionAndStrike(midiListener.noteToPlay);
        midiListener.noteToPlay = -1;
    }
}