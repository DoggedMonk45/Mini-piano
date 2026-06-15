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

    const uint16_t* GetWaveTable(WaveType Type);

}

#endif