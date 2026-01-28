#include <BLEMIDI_Transport.h>

//#include <hardware/BLEMIDI_ESP32_NimBLE.h>
#include <hardware/BLEMIDI_ESP32.h>
//#include <hardware/BLEMIDI_ArduinoBLE.h>

BLEMIDI_CREATE_INSTANCE("RainDrum", MIDI)

unsigned long t0 = millis();
bool isConnected = false;

// -----------------------------------------------------------------------------
// When BLE connected, LED will turn on (indication that connection was successful)
// When receiving a NoteOn, LED will go out, on NoteOff, light comes back on.
// This is an easy and conveniant way to show that the connection is alive and working. 
// -----------------------------------------------------------------------------
void setup()
{
    Serial.begin(115200);
    MIDI.begin();

    BLEMIDI.setHandleConnected([]() {
        isConnected = true;
        Serial.println("BLEMIDI Connected");
    });

    BLEMIDI.setHandleDisconnected([]() {
        isConnected = false;
        Serial.println("BLEMIDI Disconnected");
    });

    MIDI.setHandleNoteOn([](byte channel, byte note, byte velocity) {
        Serial.println("Note On: " + String(note) + " Vel: " + String(velocity));
    });
    MIDI.setHandleNoteOff([](byte channel, byte note, byte velocity) {
        Serial.println("Note Off: " + String(note) + " Vel: " + String(velocity));
    });
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void loop()
{
    MIDI.read();
}