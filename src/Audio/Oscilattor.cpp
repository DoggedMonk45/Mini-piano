#include "Oscillator.h"

//Uso del sistema DDS (Digital Direct Synthesis)

SR_Keypad::Oscillator::Oscillator() {

    _phase = 0;

    _frequency = 440.0f;

    _sampleRate = 8000;

    _waveTable = GetWaveTable(SINE);

    SetFrequency(_frequency);
}

void SR_Keypad::Oscillator::SetFrequency(float Frequency) {

    _frequency = Frequency;
    
    constexpr double PHASE_MAX = 4294967296.0; //Valor de 2^32
    _step = (uint32_t)((PHASE_MAX * _frequency) / _sampleRate); 
}

void SR_Keypad::Oscillator::SetSampleRate(uint32_t SampleRate) {

    _sampleRate = SampleRate;

    SetFrequency(_frequency);
}

void SR_Keypad::Oscillator::SetWave(SR_Keypad::WaveType Type) {

    _waveTable = GetWaveTable(Type);
    _phase = 0;
}

uint16_t SR_Keypad::Oscillator::Interpolate() {

   
}

uint16_t SR_Keypad::Oscillator::GenerateSample() {

    uint8_t index = _phase >> 26;

    uint8_t  next = (index == 63) ? 0 : index + 1;

    uint16_t frac = (uint16_t)((_phase & 0x03FFFFFF) >> 10); //Usar mascara para dejar solo los bits requeridos con el &

    uint16_t a = _waveTable[index];

    uint16_t b = _waveTable[next];

    //Interpolación: Se usa int pues podemos tener valores negativos del delta y con uint tendriamos overflow.

    int16_t delta = (int16_t)b - (int16_t)a;

    int32_t interp = (int32_t)delta * (int32_t)frac;

    return (uint16_t)((int16_t)a + (int16_t)(interp >> 16));
}