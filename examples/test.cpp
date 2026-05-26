#define DATA_PIN_A 13
#define Clock_PIN_A 14
#define Latch_PIN_A 15

KeypadA::SIPO_Controller.algunMetodo();

namespace KeypadA()
	void DataController(bool state) {
		digitalWrite(DATA_PIN_A, state);
	}

	void ClockController(void) {
	}

	void LatchController(void) {
	}

	SR_Keypad::SIPO SIPO_Controller(
		DataController
		ClockController
		LatchController
	);
)