#ifndef SR_KEYPAD_DAC_H
#define SR_KEYPAD_DAC_H

#include <stdint.h>

namespace Hardware {

    class DAC {
    private:

        uint8_t _address;
        uint32_t _sampleRate;

    public:

        DAC(uint8_t Address = 0x60);
        void Begin(uint32_t SampleRate = 22050);
        void Write(uint16_t Value);
        uint32_t GetSampleRate();
    };

}

#endif