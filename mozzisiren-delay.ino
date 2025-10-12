#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>
#include <mozzi_utils.h>

// -------------------- CONFIGURAÇÕES GERAIS --------------------
const int audioOutPin = 25;
const int buttonPin   = 14;
const int ledPin      = 2;

const float baseFreq = 600.0f;
const float lfoFreq  = 4.0f;
const int   lfoDepth = 100;

// Osciladores
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> mainOsc(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> lfo(SIN2048_DATA);

bool playing = false;

// -------------------- DELAY SIMPLES COM FEEDBACK --------------------
const unsigned int delayMs = 250;
const unsigned int delaySamples = (AUDIO_RATE * delayMs) / 1000;
int16_t delayBuffer[delaySamples];
unsigned int writeIndex = 0;

const int feedbackGainInt = 36;   // 36/128 ≈ 0.28
const int dryMixInt  = 77;        // ~0.6
const int wetMixInt  = 26;        // ~0.2

const int silenceThreshold = 4;   // valores absolutos menores que isso serão zerados

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
  int drySignal = playing ? mainOsc.next() : 0;

  // índice de leitura circular
  unsigned int readIndex = (writeIndex + 1) % delaySamples;
  int delayedSignal = delayBuffer[readIndex];

  // aplica feedback
  int newFeedback = (delayedSignal * feedbackGainInt) >> 7;

  // aplica threshold para remover resíduos infinitos
  if (abs(newFeedback) < silenceThreshold) {
    newFeedback = 0;
  }

  if (playing) {
    delayBuffer[writeIndex] = drySignal + newFeedback;
  } else {
    delayBuffer[writeIndex] = newFeedback;  // apenas feedback decaindo
  }

  writeIndex = (writeIndex + 1) % delaySamples;

  // mixagem seca/molhada
  int mixed = ((drySignal * dryMixInt) + (delayedSignal * wetMixInt)) >> 8;

  // segurança contra clipagem
  mixed >>= 1;

  return mixed;
}

// -------------------- LOOP --------------------
void loop() {
  audioHook();
}
