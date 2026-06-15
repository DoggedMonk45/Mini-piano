#ifndef MINI_PIANO_WAVETABLES_H
#define MINI_PIANO_WAVETABLES_H

#include <stdint.h>

namespace Mini_Piano {
    namespace Audio {

        enum WaveType {

            SINE,
            SQUARE,
            TRIANGLE,
            SAW
        };

        const uint16_t* GetWaveTable(WaveType Type);

    }
}

#endif