#include "SynthEngine.h"

Mini_Piano::Synth::SynthEngine::SynthEngine() {

    _oscillator = nullptr;
    _dac = nullptr;
    _stackSize = 0;
    _volume = 100;
    _waveType = Audio::SINE;
    _wavePending = Audio::SINE;
    _state = NORMAL;

    for (uint8_t i = 0; i < MAX_STACK; i++) {
        _noteStack[i] = 0;
    }
}

void Mini_Piano::Synth::SynthEngine::Begin(Audio::Oscillator& oscillator, Hardware::DAC& dac) {

    _oscillator = &oscillator;
    _dac = &dac;
}

void Mini_Piano::Synth::SynthEngine::Update() {

    if (!_oscillator || !_dac) return;

    // Si no hay notas en stack dar el punto medio (silencio)
    if (_stackSize == 0) {
        _dac->Write(2048);
        return;
    }

    // Generar sample (0-4095)
    uint16_t raw = _oscillator->GenerateSample();

    // Centrar en 0, aplicar volumen, volver al punto medio
    int16_t  centered = (int16_t)raw - 2048;
    int16_t  scaled = (int16_t)((int32_t)centered * _volume / 100);
    uint16_t output = (uint16_t)(scaled + 2048);

    _dac->Write(output);
}

void Mini_Piano::Synth::SynthEngine::HandleButton(uint8_t ID, bool State) {

    if (Keypad::NoteMapper::IsControl(ID)) {

        // Los controles solo se procesan al presionar (State = true)
        if (State) HandleControl(ID, State);

    }
    else {

        // Es una nota
        if (State) {
            PushNote(ID);
        }
        else {
            PopNote(ID);
        }
    }
}

void Mini_Piano::Synth::SynthEngine::PushNote(uint8_t ID) {

    // Verificar que no esté ya en la pila (evita duplicados por rebote)
    for (uint8_t i = 0; i < _stackSize; i++) {
        if (_noteStack[i] == ID) return;
    }

    // Verificar que haya espacio
    if (_stackSize >= MAX_STACK) return;

    _noteStack[_stackSize] = ID;
    _stackSize++;

    UpdateOscillator();
}

void Mini_Piano::Synth::SynthEngine::PopNote(uint8_t ID) {

    for (uint8_t i = 0; i < _stackSize; i++) {

        if (_noteStack[i] == ID) {

            // Mover todos los elementos siguientes una posición atrás
            for (uint8_t j = i; j < _stackSize - 1; j++) {
                _noteStack[j] = _noteStack[j + 1];
            }

            _stackSize--;
            break;
        }
    }

    UpdateOscillator();
}

void Mini_Piano::Synth::SynthEngine::ClearStack() {

    _stackSize = 0;
    UpdateOscillator();
}

void Mini_Piano::Synth::SynthEngine::UpdateOscillator() {

    if (!_oscillator) return;

    if (_stackSize == 0) return;

    uint8_t topID = _noteStack[_stackSize - 1];
    float   frequency = NoteMapper::GetFrequency(topID);

    _oscillator->SetFrequency(frequency);
}

void Mini_Piano::Synth::SynthEngine::HandleControl(uint8_t ID) {

    switch (ID) {
    case Keypad::BTN_SETTINGS: HandleSettings(); break;
    case Keypad::BTN_UP:       HandleUpDown(ID); break;
    case Keypad::BTN_DOWN:     HandleUpDown(ID); break;
    case Keypad::BTN_ENTER:    HandleEnter();    break;
    }
}

void Mini_Piano::Synth::SynthEngine::HandleSettings() {

    if (_state == NORMAL) {

        // Entrar a ajuste — iniciar pending con la onda actual
        _wavePending = _waveType;
        _state = AJUSTE_ONDA;

    }
    else {

        // Cancelar ajuste — descartar pending y volver a NORMAL
        _wavePending = _waveType;
        _state = NORMAL;
    }
}

void Mini_Piano::Synth::SynthEngine::HandleUpDown(uint8_t ID) {

    if (_state == NORMAL) {

        if (ID == BTN_UP && _volume < 100) _volume += 10;
        if (ID == BTN_DOWN && _volume > 0) _volume -= 10;

    }
    else { // AJUSTE_ONDA

        // Ciclamos entre SINE(0), SQUARE(1), TRIANGLE(2), SAW(3)
        // UP: avanza al siguiente, DOWN: retrocede al anterior

        uint8_t current = (uint8_t)_wavePending;

        if (ID == BTN_UP) {
            current = (current + 1) % 4;
        }
        else {
            current = (current == 0) ? 3 : current - 1;
        }

        _wavePending = (Audio::WaveType)current;
    }
}

void Mini_Piano::Synth::SynthEngine::HandleEnter() {

    if (_state != AJUSTE_ONDA) return;

    // Confirmar el cambio de onda
    _waveType = _wavePending;

    if (_oscillator) {
        _oscillator->SetWave(_waveType);
    }

    // Limpiar pila — evita notas fantasma al cambiar de onda
    ClearStack();

    _state = NORMAL;
}