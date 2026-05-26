#include "Oscillator.h"

SR_Keypad::Oscillator::Oscillator() {

    _phase = 0;

    _frequency = 440.0f;

    _sampleRate = 22050;

    _waveTable = GetWaveTable(SINE);

    SetFrequency(_frequency);
}

void SR_Keypad::Oscillator::SetFrequency(float Frequency) {

    _frequency = Frequency;

    _step = (uint32_t)((4294967296.0 * _frequency) / _sampleRate); //COrregir**
}

void SR_Keypad::Oscillator::SetSampleRate(uint32_t SampleRate) {

    _sampleRate = SampleRate;

    SetFrequency(_frequency);
}

void SR_Keypad::Oscillator::SetWave(SR_Audio::WaveType Type) {

    _waveTable = GetWaveTable(Type);
}

uint16_t SR_Keypad::Oscillator::GenerateSample() {

    _phase += _step;

    uint8_t index = _phase >> 24;

    uint8_t sample = _waveTable[index];

    // convertir 8 bits → 12 bits DAC
    return sample << 4;
}