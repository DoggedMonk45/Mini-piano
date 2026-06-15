#ifndef MINI_PIANO_SIPO_H
#define MINI_PIANO_SIPO_H

#include <stdint.h>

namespace Mini_Piano {
    namespace Hardware {

        class SIPO {
        private:
            // Apuntadores a funciones
            void(*_DataController)(bool);
            void(*_ClockController)(void);
            void(*_LatchController)(void);

        public:

            SIPO();

            SIPO(
                void(&DataController)(bool),
                void(&ClockController)(),
                void(&LatchController)()
            );

            void Write(uint8_t Data);
            void Write(uint8_t* Data, uint8_t len);

            void Data(bool x);
            void Clock();
            void Latch();

        };
    }
}

#endif//MINI_PIANO_SIPO_H