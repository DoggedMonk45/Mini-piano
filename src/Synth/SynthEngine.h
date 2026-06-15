#ifndef MINI_PIANO_SYNTHENGINE_H
#define MINI_PIANO_SYNTHENGINE_H

#include <stdint.h>
#include "../Audio/Oscillator/Oscillator.h"
#include "../Audio/WaveTables/WaveTables.h"
#include "../Hardware/DAC/DAC.h"
#include "../Keypad/NoteMapper/NoteMapper.h"

namespace Mini_Piano {
    namespace Synth {

        class SynthEngine {
        public:

            // Estados de la máquina de estados
            enum SettingsState : uint8_t {
                NORMAL,
                AJUSTE_ONDA
            };

        private:

            Audio::Oscillator* _oscillator;
            Hardware::DAC* _dac;

            // Pila de notas activas; Guarda IDs de botones presionados, el tope es la nota que suena
            static constexpr uint8_t MAX_STACK = 10;
            uint8_t _noteStack[MAX_STACK];
            uint8_t _stackSize;

            // Ajustes
            uint8_t       _volume;        // 0-100 en pasos de 10
            Audio::WaveType      _waveType;      // Onda activa confirmada
            Audio::WaveType      _wavePending;   // Onda seleccionada pero no confirmada
            SettingsState _state;         // Estado actual de la FSM (Fine State Machine)

            // Métodos privados del stack
            void PushNote(uint8_t ID);
            void PopNote(uint8_t ID);
            void ClearStack();
            void UpdateOscillator();

            // Métodos privados de la FSM 
            void HandleControl(uint8_t ID);
            void HandleSettings();
            void HandleUpDown(uint8_t ID);
            void HandleEnter();

        public:

            SynthEngine();

            // Conectar SynthEngine con Oscillator y DAC
            void Begin(Audio::Oscillator& oscillator, Hardware::DAC& dac);

            // Genera y escribe un sample al DAC
            void Update();

            void HandleButton(uint8_t ID, bool State);

        };

    }
}

#endif // SYNTH_SYNTHENGINE_H