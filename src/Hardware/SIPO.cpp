#include "SIPO.h"
#include <stdint.h>

Mini_Piano::Hardware::SIPO::SIPO() {
    _DataController = nullptr;
    _ClockController = nullptr;
    _LatchController = nullptr;
};

Mini_Piano::Hardware::SIPO::SIPO(
    void(&DataController)(bool),
    void(&ClockController)(),
    void(&LatchController)()
) {
    _DataController = DataController;
    _ClockController = ClockController;
    _LatchController = LatchController;
}

void Mini_Piano::Hardware::SIPO::Write(uint8_t Data) {

    for (uint8_t i = 0; i < 8; i++) {
        this->Data((Data >> i) & 0b1);
        Clock();
    }

    Latch();
}

void Mini_Piano::Hardware::SIPO::Write(uint8_t* Data, uint8_t len) {

    for (uint8_t i = 0; i < len * 8; i++) {
        this->Data((Data[i / 8] >> (i % 8)) & 0b1);
        Clock();
    }

    Latch();
}

void Mini_Piano::Hardware::SIPO::Data(bool x) {
    if (_DataController) { _DataController(x); }
}

void Mini_Piano::Hardware::SIPO::Clock() {
    if (_ClockController) { _ClockController(); }
}

void Mini_Piano::Hardware::SIPO::Latch() {
    if (_LatchController) { _LatchController(); }
}