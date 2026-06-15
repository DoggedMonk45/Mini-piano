#include "DAC.h"

#include <Wire.h>

Hardware::DAC::DAC(uint8_t Address) {

    _address = Address;

    _sampleRate = 22050;
}

void Hardware::DAC::Begin(uint32_t SampleRate) {

    _sampleRate = SampleRate;

    Wire.setClock(400000); // I2C fast mode

    Wire.begin();
}

void Hardware::DAC::Write(uint16_t Value) {

    Value &= 0x0FFF;

    Wire.beginTransmission(_address);

    Wire.write(0x40);

    Wire.write(Value >> 4);

    Wire.write((Value & 0x0F) << 4);

    Wire.endTransmission();
}

uint32_t Hardware::DAC::GetSampleRate() {

    return _sampleRate;
}