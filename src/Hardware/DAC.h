#ifndef MINI_PIANO_DAC_H
#define MINI_PIANO_DAC_H

#include <stdint.h>

namespace Mini_Piano {
    namespace Hardware {

        class DAC {
        private:

            uint8_t _address;
            uint32_t _sampleRate;

        public:

            DAC(uint8_t Address = 0x60);
            void Begin(uint32_t SampleRate = 8000);
            void Write(uint16_t Value);
            uint32_t GetSampleRate();
        };

    }
}

#endif