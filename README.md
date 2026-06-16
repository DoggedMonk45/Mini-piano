# Mini Piano

Librería Arduino para síntesis digital de audio por tabla de ondas (DDS)
e integración de teclado matricial de 64 teclas mediante registros de desplazamiento.

Desarrollada como proyecto final para la materia de Programación Orientada
a Objetos, Universidad Vasco de Quiroga.

## Descripción

Mini Piano implementa un sintetizador digital completo sobre un Arduino Nano,
estructurado como librería reutilizable con arquitectura orientada a objetos.
El sistema genera audio mediante Direct Digital Synthesis (DDS) con cuatro
formas de onda seleccionables, lee un teclado matricial de 8×8 teclas a través
de registros de desplazamiento, y expone una interfaz desacoplada por capas
que permite reutilizar cada módulo de forma independiente.

## Características

- Síntesis DDS con acumulador de fase de 32 bits e interpolación lineal
- Cuatro formas de onda: seno, cuadrada, triangular y sierra (LUT de 64 muestras a 12 bits)
- Soporte para DAC MCP4725 vía I²C
- Driver para registro de desplazamiento de entrada PISO (74HC165)
- Driver para registro de desplazamiento de salida SIPO (74HC595)
- Escaneo de matriz de teclado 8×8 (64 teclas) con detección de flancos
- Pila de notas activas con política last-note priority (hasta 10 notas)
- Control de volumen en pasos del 10% mediante botones dedicados
- Máquina de estados finitos (FSM) para selección de forma de onda en tiempo real
- Arquitectura completamente desacoplada mediante punteros a funciones (HAL)

## Hardware requerido

| Componente | Descripción |
|---|---|
| Arduino Nano (ATmega328P) | Microcontrolador principal |
| MCP4725 | DAC I²C de 12 bits para salida de audio |
| 74HC595 | Registro de desplazamiento SIPO para activar columnas del teclado |
| 74HC165 | Registro de desplazamiento PISO para leer filas del teclado |
| Matriz de pulsadores 8×8 | 60 teclas musicales + 4 botones de control |

## Estructura de la librería
Mini_Piano/

├── examples/

│   ├── DAC_Oscillator/     # Prueba básica del oscilador y DAC

│   ├── Keypad/             # Prueba del escaneo del teclado

│   └── Todo/               # Ejemplo completo integrado

├── src/

│   ├── Audio/

│   │   ├── Oscillator.h / .cpp     # Oscilador DDS con interpolación lineal

│   │   └── WaveTables.h / .cpp     # LUT de las cuatro formas de onda

│   ├── Hardware/

│   │   ├── DAC.h / .cpp            # Driver MCP4725 vía I²C

│   │   ├── PISO.h / .cpp           # Driver 74HC165

│   │   └── SIPO.h / .cpp           # Driver 74HC595

│   ├── Keypad/

│   │   ├── Keypad.h / .cpp         # Controlador de la matriz 8×8

│   │   └── NoteMapper.h / .cpp     # Mapeo de IDs a frecuencias musicales

│   ├── Synth/

│   │   └── SynthEngine.h / .cpp    # Motor central: pila de notas y FSM

│   └── Mini_Piano.h                # Header maestro

├── library.properties

└── README.md

## Instalación

1. Descarga o clona este repositorio.
2. Copia la carpeta `Mini_Piano` a la carpeta `libraries` de tu instalación de Arduino.
3. Reinicia el IDE de Arduino.
4. La librería estará disponible en **Archivo → Ejemplos → Mini_Piano**.

## Uso básico

```cpp
#include <Mini_Piano.h>

// Definir funciones de control para PISO y SIPO
bool  PISO_Data()  { return digitalRead(4); }
void  PISO_Clock() { digitalWrite(3, HIGH); digitalWrite(3, LOW); }
void  PISO_SL()    { digitalWrite(2, LOW);  digitalWrite(2, HIGH); }
void  SIPO_Data(bool v) { digitalWrite(7, v); }
void  SIPO_Clock() { digitalWrite(6, HIGH); digitalWrite(6, LOW); }
void  SIPO_Latch() { digitalWrite(5, HIGH); digitalWrite(5, LOW); }

Mini_Piano::Hardware::PISO     myPISO(PISO_Data, PISO_Clock, PISO_SL);
Mini_Piano::Hardware::SIPO     mySIPO(SIPO_Data, SIPO_Clock, SIPO_Latch);
Mini_Piano::Hardware::DAC      myDAC;
Mini_Piano::Audio::Oscillator  myOscillator;
Mini_Piano::Synth::SynthEngine mySynth;
Mini_Piano::Keypad::Controller myKeypad;

void onKey(uint8_t ID, bool State) {
    mySynth.HandleButton(ID, State);
}

void setup() {
    myDAC.Begin(8000);
    myOscillator.SetSampleRate(8000);
    mySynth.Begin(myOscillator, myDAC);
    myKeypad.AttachCallback(onKey);
    myKeypad.AttachSIPO(mySIPO);
    myKeypad.AttachPISO(myPISO);
}

void loop() {
    mySynth.Update();
    myKeypad.Scan();
}
```

## Controles del teclado

| Botón | ID | Estado NORMAL | Estado AJUSTE_ONDA |
|---|---|---|---|
| DOWN | 39 | Volumen -10% | Forma de onda anterior |
| UP | 47 | Volumen +10% | Forma de onda siguiente |
| ENTER | 55 | — | Confirmar forma de onda |
| SETTINGS | 63 | Entrar a AJUSTE_ONDA | Cancelar y volver |

## Limitaciones conocidas

- El sample rate efectivo se ve reducido por la latencia del protocolo I²C y el escaneo
  del teclado compitiendo en el mismo ciclo principal. Se recomienda migrar a un DAC
  con interfaz SPI para aplicaciones que requieran mayor fidelidad de audio.
- Las tablas de onda se almacenan en SRAM. Una mejora pendiente es migrarlas a
  Flash mediante `PROGMEM` para liberar ~512 bytes de memoria dinámica.
- La FSM de cambio de forma de onda presenta comportamiento inconsistente bajo
  carga alta del ciclo principal. En investigación.

## Autor

Juan Pablo García Olivares — Universidad Vasco de Quiroga, 2026
