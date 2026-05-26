#ifndef SR_KEYPAD_NOTEMAPPER_H
#define SR_KEYPAD_NOTEMAPPER_H

#include <stdint.h>

namespace SR_Keypad {

    struct NoteInfo {

        const char* Name;
        float Frequency;
    };

    class NoteMapper {
    private:

        static const NoteInfo NOTES[128];

    public:

        static float GetFrequency(uint8_t NoteID);

        static const char* GetName(uint8_t NoteID);
    };

}

#endif 