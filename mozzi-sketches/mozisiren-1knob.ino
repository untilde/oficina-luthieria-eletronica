#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>
#include <mozzi_utils.h>

// -------------------- CONFIGURAÇÕES GERAIS --------------------
const int audioOutPin = 25;    // DAC1 no ESP32
const int buttonPin   = 14;    // Botão
const int ledPin      = 2;     // LED embutido
const int potPin      = 34;    // Potenciômetro (ADC)

// Sirene
const float baseFreq = 600.0f;
const int   lfoDepth = 100;

// Osciladores
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> mainOsc(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> lfo(SIN2048_DATA);

bool playing = false;

// -------------------- SETUP --------------------
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLDOWN);

  mainOsc.setFreq(baseFreq);
  lfo.setFreq(2.0f); // frequência inicial

  startMozzi();
}

// -------------------- CONTROLE --------------------
void updateControl() {
  playing = (digitalRead(buttonPin) == HIGH);

  // leitura do potenciômetro (0 a 4095)
  int potValue = mozziAnalogRead(potPin);

  // mapeia para faixa de 0.1Hz a 10Hz
  float lfoFreq = 0.1f + (potValue / 4095.0f) * 9.9f;
  lfo.setFreq(lfoFreq);

  if (playing) {
    digitalWrite(ledPin, HIGH);
    int16_t mod = lfo.next();
    int16_t modAmount = (mod * lfoDepth) >> 7;
    mainOsc.setFreq(baseFreq + modAmount);
  } else {
    digitalWrite(ledPin, LOW);
    mainOsc.setFreq(0);
  }
}

// -------------------- ÁUDIO --------------------
int updateAudio() {
  return playing ? mainOsc.next() : 0;
}

// -------------------- LOOP --------------------
void loop() {
  audioHook();
}
