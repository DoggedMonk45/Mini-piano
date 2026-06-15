#ifndef SR_KEYPAD_OSCILLATOR_H
#define SR_KEYPAD_OSCILLATOR_H

#include <stdint.h>

#include "../WaveTables/WaveTables.h"

namespace SR_Keypad {

    class Oscillator {
    private:

        uint32_t _phase;
        uint32_t _step;

        float _frequency;
        uint32_t _sampleRate;

        const uint16_t* _waveTable;

    public:

        Oscillator();

        void SetFrequency(float Frequency);

        void SetSampleRate(uint32_t SampleRate);

        void SetWave(SR_Audio::WaveType Type);

        uint16_t GenerateSample();

    };

}

#endif