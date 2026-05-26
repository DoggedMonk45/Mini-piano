#include "NoteMapper.h"

namespace {

    // 64 notas desde C4
    const float NOTE_FREQUENCIES[64] = {

        261.63f, // C4
        277.18f, // C#4
        293.66f, // D4
        311.13f, // D#4
        329.63f, // E4
        349.23f, // F4
        369.99f, // F#4
        392.00f, // G4
        415.30f, // G#4
        440.00f, // A4
        466.16f, // A#4
        493.88f, // B4

        523.25f, // C5
        554.37f,
        587.33f,
        622.25f,
        659.25f,
        698.46f,
        739.99f,
        783.99f,
        830.61f,
        880.00f,
        932.33f,
        987.77f,

        1046.50f, // C6
        1108.73f,
        1174.66f,
        1244.51f,
        1318.51f,
        1396.91f,
        1479.98f,
        1567.98f,
        1661.22f,
        1760.00f,
        1864.66f,
        1975.53f,

        2093.00f, // C7
        2217.46f,
        2349.32f,
        2489.02f,
        2637.02f,
        2793.83f,
        2959.96f,
        3135.96f,
        3322.44f,
        3520.00f,
        3729.31f,
        3951.07f,

        4186.01f, // C8
        4434.92f,
        4698.64f,
        4978.03f,
        5274.04f,
        5587.65f,
        5919.91f,
        6271.93f,
        6644.88f,
        7040.00f,
        7458.62f,
        7902.13f,

        8372.02f,
        8869.84f,
        9397.27f,
        9956.06f
    };

    float NoteMapper::GetFrequency(uint8_t NoteID) {

        if (NoteID >= 128) {
            return 0;
        }

        return NOTES[NoteID].Frequency;
    }

    const char* NoteMapper::GetName(uint8_t NoteID) {

        if (NoteID >= 128) {
            return "";
        }

        return NOTES[NoteID].Name;
    }

}