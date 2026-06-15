#include <Mini_Piano.h>

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

//Instancias
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

//Callback
void KeypadCallback(uint8_t ID, bool State) {

	Serial.print(State ? "Presionado - ID: " : "Soltado - ID: ");
	Serial.print(ID);

	if (Mini_Piano::Keypad::NoteMapper::IsControl(ID)) {

		Serial.print(" [Control] ");

		switch (ID) {

		case Mini_Piano::Keypad::BTN_DOWN:

			Serial.print("DOWN");

		case Mini_Piano::Keypad::BTN_UP:

			Serial.print("UP");

		case Mini_Piano::Keypad::BTN_ENTER:

			Serial.print("ENTER");

		case Mini_Piano::Keypad::BTN_SETTINGS:

			Serial.print("SETTINGS");

		default:
			break;
		}
	}
	else {
		Serial.print(" [Nota] ");
		Serial.print(Mini_Piano::Keypad::NoteMapper::GetFrequency(ID));
		Serial.print(" HZ");
	}

	Serial.println();
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

	myKeypad.AttachSIPO(mySIPO);
	myKeypad.AttachPISO(myPISO);
}

void loop() {
	myKeypad.Scan();

}