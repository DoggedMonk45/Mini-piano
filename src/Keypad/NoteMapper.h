#ifndef SR_KEYPAD_NOTEMAPPER_H
#define SR_KEYPAD_NOTEMAPPER_H

#include <stdint.h>

namespace SR_Keypad {

    // IDs de los botones de control
    constexpr uint8_t BTN_DOWN = 39;
    constexpr uint8_t BTN_UP = 47;
    constexpr uint8_t BTN_ENTER = 55;
    constexpr uint8_t BTN_SETTINGS = 63;

    class NoteMapper {
    public:

        static float GetFrequency(uint8_t ButtonID);

        static bool IsControl(uint8_t ButtonID);

    };

}

#endif // SR_KEYPAD_NOTEMAPPER_H