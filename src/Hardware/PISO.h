#ifndef MINI_PIANO_PISO_H
#define MINI_PIANO_PISO_H

#include <stdint.h>

namespace Mini_Piano {
    namespace Hardware {

        class PISO {
        private:
            // Apuntadores a funciones
            bool(*_DataController)();          // Data In
            void(*_ClockController)(void);     // Clock
            void(*_SLController)(void);        // Shift Load

        public:

            PISO();

            PISO(
                bool(&DataController)(),
                void(&ClockController)(),
                void(&SLController)()
            );

            uint8_t Read(uint8_t bits);
            uint8_t* ReadArray(uint8_t bytes, uint8_t* buffer);

        };
    }
}

#endif//HARDWARE_PISO_H