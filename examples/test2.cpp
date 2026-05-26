#include <SR_Keypad.h>

SR_Keypad::DAC dac;

SR_Keypad::SynthEngine synth;

void setup() {

    dac.Begin(11025);

    synth.AttachDAC(dac);

    synth.SetWave(SR_Keypad::SINE);

    synth.SetFrequency(440);
}

void loop() {

    synth.Update();
}