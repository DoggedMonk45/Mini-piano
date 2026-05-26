#include "WaveTables.h"

namespace { //Namespace sin definición para hacerlo "Privado respecto al archivo"**

    const uint8_t SINE_WAVE[256] = {
        // valores seno
    };

    const uint8_t SQUARE_WAVE[256] = {
        // valores cuadrada
    };

    const uint8_t TRIANGLE_WAVE[256] = {
        // valores triangular
    };

    const uint8_t SAW_WAVE[256] = {
        // valores sierra
    };

}

const uint8_t* SR_Audio::GetWaveTable(WaveType type) {

    switch (type) {

    case SINE:
        return SINE_WAVE;

    case SQUARE:
        return SQUARE_WAVE;

    case TRIANGLE:
        return TRIANGLE_WAVE;

    case SAW:
        return SAW_WAVE;

    default:
        return SINE_WAVE;
    }
}