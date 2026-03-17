#include "Sintetizador.h"
#include <Arduino.h>

void Sintetizador::tocarNota(float frecuencia) {
	tone(8, frecuencia)
}