#indef SR_Keypad_DAC_H
#define SR_Keypad_DAC_H

#include <stdint.h>

namespace SR_Keypad {
	class DAC {
		private:
			uint32_t _sampleRate;
			void (*_writeDAC)(uint16_t);
		public:
			//El hardware es un DAC, el modelo del hardware es el MCP2745 el cual usare en conjunto con el Arduino a través de R2R para poder hacer el paso de las señales de los botones a lograr que sea un sonido audible.
	};
}