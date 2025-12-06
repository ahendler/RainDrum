#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32.h>

#include "notes.h"
#include "MidiBle.h"


int MidiBle::noteToPlay = -1; // 0 to 7
BLEMIDI_CREATE_INSTANCE("RainDrum", MIDI);

MidiBle::MidiBle() {}

void MidiBle::initialize() {
    MIDI.begin();

    BLEMIDI.setHandleConnected([]() {
        Serial.println("BLEMIDI Connected");
    });

    BLEMIDI.setHandleDisconnected([]() {
        Serial.println("BLEMIDI Disconnected");
    });

    MIDI.setHandleNoteOn([](byte channel, byte note, byte velocity) {
        Serial.println("Note On: " + String(note) + " Vel: " + String(velocity));
        int position = MidiBle::getNotePosition(note);
        if (position != -1) {
            MidiBle::noteToPlay = position;
        }
    });

    MIDI.setHandleNoteOff([](byte channel, byte note, byte velocity) {
        Serial.println("Note Off: " + String(note) + " Vel: " + String(velocity));
    });
}

void MidiBle::read() {
    MIDI.read();
}

int MidiBle::getNotePosition(int note) {
    for (int i = 0; i < 8; i++) {
        if (drumNotes[i] == note) {
            return i;
        }
    }
    return -1;
}