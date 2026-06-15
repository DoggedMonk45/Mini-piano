#include <Mini_Piano.h>

//Instancias
Mini_Piano::Hardware::DAC myDac;
Mini_Piano::Audio::Oscillator myOscillator;

//Nombre de Ondas para el Monitor Serial
const char* waveNames[] = {"SINE", "SQUARE", "TRIANGLE", "SAW"};
uint8_t currentWave = 0;
unsigned long lastChange = 0;

void setup() {

    dac.Begin(11025);

    myDac.Begin(8000);

    myOscillator.SetSampleRate(8000);
    myOscillator.SetFrequency(440.0f);
    myOscillator.SetWave(Mini_Piano::Audio::SINE);

    Serial.println("Mini Piano - Prueba DAC + Oscillator");
    Serial.println("Onda actual: SINE @ 440 HZ");
}

void loop() {

    //Generar onda y escribir en el DAC
    myDac.Write(myOscillator.GenerateSample());

    //Cambiar onda cada 5s
    if (millis() - lastChange >= 5000) {

        lastChange = millis();

        currentWave = (currentWave + 1) % 4;
        myOscillator.SetWave((Mini_Piano::Audio::WaveType)currentWave);

        Serial.print("Cambiando a: ");
        Serial.println(waveNames[currentWave]);
    }
}