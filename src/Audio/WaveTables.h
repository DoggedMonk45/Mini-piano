#ifndef SR_KEYPAD_WAVETABLES_H
#define SR_KEYPAD_WAVETABLES_H

#include <stdint.h>

namespace SR_Keypad {

    enum WaveType {

        SINE,
        SQUARE,
        TRIANGLE,
        SAW
    };

    const uint8_t* GetWaveTable(WaveType Type);

}

#endif