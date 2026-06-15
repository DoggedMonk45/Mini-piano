#include "NoteMapper.h"

namespace {

    // 64 notas desde C4
    const float NOTE_FREQUENCIES[64] = {
        2637.02f,  // ID  0 - E7
        1661.22f,  // ID  1 - G#6
        1046.50f,  // ID  2 - C6
         659.26f,  // ID  3 - E5
         415.30f,  // ID  4 - G#4
         261.63f,  // ID  5 - C4
         164.81f,  // ID  6 - E3
         130.81f,  // ID  7 - C3
        2793.83f,  // ID  8 - F7
        1760.00f,  // ID  9 - A6
        1108.73f,  // ID 10 - C#6
         698.46f,  // ID 11 - F5
         440.00f,  // ID 12 - A4
         277.18f,  // ID 13 - C#4
         174.61f,  // ID 14 - F3
         138.59f,  // ID 15 - C#3
        2959.96f,  // ID 16 - F#7
        1864.66f,  // ID 17 - A#6
        1174.66f,  // ID 18 - D6
         739.99f,  // ID 19 - F#5
         466.16f,  // ID 20 - A#4
         293.66f,  // ID 21 - D4
         185.00f,  // ID 22 - F#3
         146.83f,  // ID 23 - D3
        3135.96f,  // ID 24 - G7
        1975.53f,  // ID 25 - B6
        1244.51f,  // ID 26 - D#6
         783.99f,  // ID 27 - G5
         493.88f,  // ID 28 - B4
         311.13f,  // ID 29 - D#4
         196.00f,  // ID 30 - G3
         155.56f,  // ID 31 - D#3
        3322.44f,  // ID 32 - G#7
        2093.00f,  // ID 33 - C7
        1318.51f,  // ID 34 - E6
         830.61f,  // ID 35 - G#5
         523.25f,  // ID 36 - C5
         329.63f,  // ID 37 - E4
         207.65f,  // ID 38 - G#3
           0.0f,   // ID 39 - Control (DOWN)
        3520.00f,  // ID 40 - A7
        2217.46f,  // ID 41 - C#7
        1396.91f,  // ID 42 - F6
         880.00f,  // ID 43 - A5
         554.37f,  // ID 44 - C#5
         349.23f,  // ID 45 - F4
         220.00f,  // ID 46 - A3
           0.0f,   // ID 47 - Control (UP)
        3729.31f,  // ID 48 - A#7
        2349.32f,  // ID 49 - D7
        1479.98f,  // ID 50 - F#6
         932.33f,  // ID 51 - A#5
         587.33f,  // ID 52 - D5
         369.99f,  // ID 53 - F#4
         233.08f,  // ID 54 - A#3
           0.0f,   // ID 55 - Control (ENTER)
        3951.07f,  // ID 56 - B7
        2489.02f,  // ID 57 - D#7
        1567.98f,  // ID 58 - G6
         987.77f,  // ID 59 - B5
         622.25f,  // ID 60 - D#5
         392.00f,  // ID 61 - G4
         246.94f,  // ID 62 - B3
           0.0f    // ID 63 - Control (SET)
    };
}
float Mini_Piano::Keypad::NoteMapper::GetFrequency(uint8_t NoteID) {
    if (NoteID >= 64) {
        return 0.0f;
    }
    
    return NOTE_FREQUENCIES[NoteID];
}

bool Mini_Piano::Keypad::NoteMapper::IsControl(uint8_t ButtonID) {

    return ButtonID == BTN_DOWN ||
        ButtonID == BTN_UP ||
        ButtonID == BTN_ENTER ||
        ButtonID == BTN_SETTINGS;

}