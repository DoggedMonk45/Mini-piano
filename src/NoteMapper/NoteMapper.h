#ifndef SR_KEYPAD_NOTEMAPPER_H
#define SR_KEYPAD_NOTEMAPPER_H

#include <stdint.h>

namespace SR_Keypad {

    class NoteMapper {
    private:

        float _frequencies[64];

    public:

        NoteMapper();

        float GetFrequency(uint8_t ID);

    };

}

#endif //SR_KEYPAD_NOTEMAPPER_H