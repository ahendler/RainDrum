/**
 * The Rain drum has 8 positions with notes in the order: [C1, G, E, B, F, C2, D, A]
 * Using C3 (middle C) as the base octave (just to match MIDI KeyBoard app)
 */

#ifndef NOTES_H
#define NOTES_H

#define REST    0
#define NOTE_C4 48  // C
#define NOTE_D4 50
#define NOTE_E4 52
#define NOTE_F4 53
#define NOTE_G4 55
#define NOTE_A4 57
#define NOTE_B4 59
#define NOTE_C5 60  // C above middle C

// Drum note mapping
// Position: 0      1      2      3      4      5      6      7
// Order:   [C1,    G,     E,     B,     F,     C2,    D,     A]
const int drumNotes[8] = {
    NOTE_C4,  // Position 0: C1 (lower C)
    NOTE_G4,  // Position 1: G
    NOTE_E4,  // Position 2: E
    NOTE_B4,  // Position 3: B
    NOTE_F4,  // Position 4: F
    NOTE_C5,  // Position 5: C2 (upper C)
    NOTE_D4,  // Position 6: D
    NOTE_A4   // Position 7: A
};

#endif
