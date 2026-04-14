#include "NoteMapper.h"

SR_Keypad::NoteMapper::NoteMapper() {

    // Escala básica (ejemplo: 64 teclas)
    float baseFreq = 261.63; // C4

    for (uint8_t i = 0; i < 64; i++) {
        _frequencies[i] = baseFreq * pow(2.0, i / 12.0); //Entre 12 para ir cambiando de octava
    }
}

float SR_Keypad::NoteMapper::GetFrequency(uint8_t ID) {

    if (ID >= 64) {
        return 0;
    }

    return _frequencies[ID];
}