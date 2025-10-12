#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>

// -------------------- CONFIGURAÇÕES GERAIS --------------------
const int audioOutPin = 25;    // DAC1 no ESP32
const int buttonPin   = 14;    // Botão
const int ledPin      = 2;     // LED embutido

const float baseFreq = 600.0f;  // Frequência base do Dub Siren
const float lfoFreq  = 4.0f;    // Frequência de modulação
const float lfoDepth = 100.0f;  // Profundidade da modulação

// Osciladores
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> mainOsc(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> lfo(SIN2048_DATA);

bool playing = false;

// -------------------- DELAY SIMPLES COM FEEDBACK --------------------
const unsigned int delayMs = 250;  // tempo em ms
const unsigned int delaySamples = (AUDIO_RATE * delayMs) / 1000;
int16_t delayBuffer[delaySamples];
unsigned int writeIndex = 0;

const float feedbackGain = 0.35f;  // 0.0 a 1.0 (cauda do delay)
const float dryMix = 0.6f;
const float wetMix = 0.2f;

// -------------------- SETUP --------------------
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLDOWN);

  mainOsc.setFreq(baseFreq);
  lfo.setFreq(lfoFreq);

  for (unsigned int i = 0; i < delaySamples; i++) {
    delayBuffer[i] = 0;
  }

  startMozzi();
}

// -------------------- CONTROLE --------------------
void updateControl() {
  playing = (digitalRead(buttonPin) == HIGH);

  if (playing) {
    digitalWrite(ledPin, HIGH);
    int mod = lfo.next();
    float modAmount = (mod / 128.0f) * lfoDepth;
    mainOsc.setFreq(baseFreq + modAmount);
  } else {
    digitalWrite(ledPin, LOW);
    mainOsc.setFreq(0);
  }
}

// -------------------- ÁUDIO --------------------
int updateAudio() {
  int drySignal = playing ? mainOsc.next() : 0;

  // índice de leitura (circular)
  unsigned int readIndex = (writeIndex + 1) % delaySamples;
  int delayedSignal = delayBuffer[readIndex];

  // escreve com feedback
  delayBuffer[writeIndex] = drySignal + (int)(delayedSignal * feedbackGain);
  writeIndex = (writeIndex + 1) % delaySamples;

  // mix final com divisor de segurança
  int mixed = (int)(drySignal * dryMix + delayedSignal * wetMix);
  mixed = mixed / 2;  // reduz o ganho geral e previne clipagem

  return mixed;
}

void loop() {
  audioHook();
}
