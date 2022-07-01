#include <Arduino.h>
#include <AiEsp32RotaryEncoder.h>
#include <Encoder.h>
#include <OneButton.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

#define ROTARY_ENCODER_A_PIN 32
#define ROTARY_ENCODER_B_PIN 33
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENOCDER_STEPS 5

#define encBtn 27

#define LED_STRIP_A_PIN 5
#define LED_STRIP_B_PIN 18
#define NUM_LEDS 300

enum State { BRIGHTNESS, COLOR, PALETTE };

CRGB ledStripA[NUM_LEDS] = {0};
CRGB ledStripB[NUM_LEDS] = {0};
int brightness = 60;
int brightnessMax = 120;
int powerLimit = 5000;
int paletteIndex = 0;

#include "palettes.h"

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, 15, ROTARY_ENCODER_VCC_PIN, ROTARY_ENOCDER_STEPS);

OneButton btn = OneButton (
    encBtn,
    true,
    true
);

static void handleClick() {
  Serial.println("Single Clicked");
}

static void handleDoubleClick() {
  Serial.println("Double Clicked!");
}

static void handleLongClick() {
  Serial.println("Long clicked!");
}

void rotary_loop() {
  if (rotaryEncoder.encoderChanged()) {
    Serial.print("Value: ");
    Serial.println(rotaryEncoder.readEncoder());
  }
}

void IRAM_ATTR readEncoderISR(){
  rotaryEncoder.readEncoder_ISR();
}

void setup() {
  // Setup Serial
  Serial.begin(115200);
  Serial.println("Started sketch");

  // Setup rotary encoder
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  bool circleValues = false;
  rotaryEncoder.setBoundaries(0, 1000, circleValues);
  rotaryEncoder.setAcceleration(250);

  // Setup Buttons
  btn.attachClick(handleClick);
  btn.attachDoubleClick(handleDoubleClick);
  btn.attachLongPressStart(handleLongClick);

  // Setup LED strips
  FastLED.addLeds<WS2812B, LED_STRIP_A_PIN, GRB>(ledStripA, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_STRIP_B_PIN, GRB>(ledStripB, NUM_LEDS);
  FastLED.setBrightness(brightness);
  FastLED.setMaxPowerInMilliWatts(powerLimit);
  FastLED.show();
}

void loop() {
  rotary_loop();
  btn.tick();
  
  fill_rainbow(ledStripA, NUM_LEDS, paletteIndex, 2.55);
  fill_rainbow(ledStripB, NUM_LEDS, paletteIndex, 2.55);
  FastLED.delay(5);
  paletteIndex++;
  FastLED.setBrightness(brightness);
}

