#include <Mini_Piano.h>

//Pines
#define PISO_DATA_PIN   4
#define PISO_CLOCK_PIN  3
#define PISO_SL_PIN     2
#define SIPO_DATA_PIN  5
#define SIPO_CLOCK_PIN 6
#define SIPO_LATCH_PIN 7

//Controladores PISO
bool PISO_DataController() {
	return digitalRead(PISO_DATA_PIN);
}

void PISO_ClockController(void) {
	digitalWrite(PISO_CLOCK_PIN, 1);
	digitalWrite(PISO_CLOCK_PIN, 0);
}

void PISO_SLController(void) {
	digitalWrite(PISO_SL_PIN, 0);
	digitalWrite(PISO_SL_PIN, 1);
}

//Controladores SIPO
void SIPO_DataController(bool value) {
	digitalWrite(SIPO_DATA_PIN, value);
}

void SIPO_ClockController(void) {
	digitalWrite(SIPO_CLOCK_PIN, 1);
	digitalWrite(SIPO_CLOCK_PIN, 0);
}

void SIPO_LatchController(void) {
	digitalWrite(SIPO_LATCH_PIN, 1);
	digitalWrite(SIPO_LATCH_PIN, 0);
}

//Instancias de Hardware
Mini_Piano::Hardware::PISO myPISO(
	PISO_DataController,
	PISO_ClockController,
	PISO_SLController
);

Mini_Piano::Hardware::SIPO mySIPO(
	SIPO_DataController,
	SIPO_ClockController,
	SIPO_LatchController
);
Mini_Piano::Hardware::DAC myDAC;

//Instancia de Audio
Mini_Piano::Audio::Oscillator myOscillator;

//Instancia de Synth
Mini_Piano::Synth::SynthEngine mySynth;

//Callback del Keypad
void KeypadCallback(uint8_t ID, bool State) {
	mySynth.HandleButton(ID,State)
}

Mini_Piano::Keypad::Controller myKeypad(KeypadCallback);

//Setup
void setup() {

	Serial.begin(115200);

	pinMode(PISO_DATA_PIN, INPUT);
	pinMode(PISO_CLOCK_PIN, OUTPUT);
	pinMode(PISO_SL_PIN, OUTPUT);
	pinMode(SIPO_DATA_PIN, OUTPUT);
	pinMode(SIPO_CLOCK_PIN, OUTPUT);
	pinMode(SIPO_LATCH_PIN, OUTPUT);

	myDAC.Begin(8000);
	mySynth.Begin(myOscillator, myDAC);

	myKeypad.AttachSIPO(mySIPO);
	myKeypad.AttachPISO(myPISO);

	Serial.println("Mini Piano listo.");
	Serial.println("Controles: UP/DOWN = Volumen | SETTINGS = cambiar onda | ENTER = Confirmar cambios.");
}

//Loop
void loop() {
	myKeypad.Scan(); //Leer estqado de botones y disparar Callbacks

	mySynth.Update(); //Mantener actualizado el DAC escribiendole los ultimos datos generados.

}