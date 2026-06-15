#ifndef MINI_PIANO_OSCILLATOR_H
#define MINI_PIANO_OSCILLATOR_H

#include <stdint.h>

#include "../WaveTables/WaveTables.h"

namespace Mini_Piano {
    namespace Audio {

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

            void SetWave(WaveType Type);

            uint16_t GenerateSample();

        };

    }
}

#endif