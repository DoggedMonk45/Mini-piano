#ifndef MINI_PIANO_KEYPAD_H
#define MINI_PIANO_KEYPAD_H

#include <stdint.h>

#include "../../Hardware/SIPO/SIPO.h"
#include "../../Hardware/PISO/PISO.h"

namespace Mini_Piano {
    namespace Keypad {

        class Controller {
        public:

            enum StatusKeys : uint8_t {
                Rising = 0b00,
                Falling = 0b01,
                IdleHigh = 0b10,
                IdleLow = 0b11
            };

        private:

            Hardware::SIPO* _out_controller;
            Hardware::PISO* _in_controller;

            uint8_t _prev_states[8];

            void(*_Callback)(uint8_t ID, bool State);

        public:

            Controller();
            Controller(void(&Callback)(uint8_t ID, bool State));

            void AttachCallback(void(&Callback)(uint8_t ID, bool State));
            void ClearCallback();

            void AttachSIPO(Hardware::SIPO& SIPO_Controller);
            void DettachSIPO();

            void AttachPISO(Hardware::PISO& PISO_Controller);
            void DettachPISO();


            void Scan();

        };

    }
}

#endif//MINI_PIANO_KEYPAD_H