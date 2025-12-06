#include "Drum.h"
#include "MidiBle.h"

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