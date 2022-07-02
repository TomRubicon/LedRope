#include <Arduino.h>
#include <AiEsp32RotaryEncoder.h>
#include <Encoder.h>
#include <OneButton.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

#define ROTARY_ENCODER_A_PIN 32
#define ROTARY_ENCODER_B_PIN 33
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENOCDER_STEPS 4

#define encBtn 27

#define LED_STRIP_A_PIN 5
#define LED_STRIP_B_PIN 18
#define NUM_LEDS 300

enum STATES { SPEED, DENSITY, PALETTE };

CRGB ledStripA[NUM_LEDS] = {0};
CRGB ledStripB[NUM_LEDS] = {0};
int brightness = 100;
int brightnessMax = 100;
int powerLimit = 5000;
int paletteIndex = 0;
int speed = 10;
float density = 1;
int paletteId = 0;
int state = 0;

#include "palettes.h"

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, 15, ROTARY_ENCODER_VCC_PIN, ROTARY_ENOCDER_STEPS);

OneButton btn = OneButton (
    encBtn,
    true,
    true
);

float readEncoderFloat() {
  return (float)rotaryEncoder.readEncoder() / 100.0;
}

static void handleClick() {
  Serial.println("Single Clicked: Entering speed mode");
  state = STATES::SPEED;
  rotaryEncoder.setBoundaries(0, 100, false);
  rotaryEncoder.setEncoderValue(speed);
  rotaryEncoder.setAcceleration(25);
}

static void handleDoubleClick() {
  Serial.println("Double Clicked: Entering density mode");
  state = STATES::DENSITY;
  rotaryEncoder.setBoundaries(1 * 100, 10 * 100, false);
  int densityInt = density * 100;
  rotaryEncoder.setEncoderValue(densityInt);
  rotaryEncoder.setAcceleration(400);
}

static void handleLongClick() {
  Serial.println("Long clicked: Entering palette/color change mode");
  state = STATES::PALETTE;
  rotaryEncoder.setBoundaries(0, 7, true);
  rotaryEncoder.setEncoderValue(paletteId);
  rotaryEncoder.setAcceleration(0);
}

void rotary_loop() {
  if (rotaryEncoder.encoderChanged()) {
    Serial.print("Value: ");

    if (state == STATES::SPEED) {
      Serial.println(rotaryEncoder.readEncoder());
      speed = rotaryEncoder.readEncoder();
    } else if (state == STATES::DENSITY) {
      Serial.println(readEncoderFloat());
      density = readEncoderFloat();
    } else {
      Serial.println(rotaryEncoder.readEncoder());
      paletteId = rotaryEncoder.readEncoder();
    }
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
  rotaryEncoder.setBoundaries(0, 100, circleValues);
  rotaryEncoder.setAcceleration(25);

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
  btn.tick();
  rotary_loop();

  if (paletteId == 0) {
    fill_palette(ledStripA, NUM_LEDS, paletteIndex, density, sunset1, 100, LINEARBLEND);
    fill_palette(ledStripB, NUM_LEDS, paletteIndex, density, sunset1, 100, LINEARBLEND);
  } else if (paletteId == 1) {
    fill_palette(ledStripA, NUM_LEDS, paletteIndex, density, sunset2, 100, LINEARBLEND);
    fill_palette(ledStripB, NUM_LEDS, paletteIndex, density, sunset2, 100, LINEARBLEND);
  } else if (paletteId == 2) {
    fill_palette(ledStripA, NUM_LEDS, paletteIndex, density, sanjaun, 100, LINEARBLEND);
    fill_palette(ledStripB, NUM_LEDS, paletteIndex, density, sanjaun, 100, LINEARBLEND);
  } else if (paletteId == 3) {
    fill_palette(ledStripA, NUM_LEDS, paletteIndex, density, fire, 100, LINEARBLEND);
    fill_palette(ledStripB, NUM_LEDS, paletteIndex, density, fire, 100, LINEARBLEND);
  } else if (paletteId == 4) {
    fill_palette(ledStripA, NUM_LEDS, paletteIndex, density, outrun1, 100, LINEARBLEND);
    fill_palette(ledStripB, NUM_LEDS, paletteIndex, density, outrun1, 100, LINEARBLEND);
  } else if (paletteId == 5) {
    fill_palette(ledStripA, NUM_LEDS, paletteIndex, density, outrun2, 100, LINEARBLEND);
    fill_palette(ledStripB, NUM_LEDS, paletteIndex, density, outrun2, 100, LINEARBLEND);
  } else if (paletteId == 6) {
    fill_palette(ledStripA, NUM_LEDS, paletteIndex, density, outrun3, 100, LINEARBLEND);
    fill_palette(ledStripB, NUM_LEDS, paletteIndex, density, outrun3, 100, LINEARBLEND);
  } else if (paletteId == 7) {
    fill_rainbow(ledStripA, NUM_LEDS, paletteIndex, density);
    fill_rainbow(ledStripB, NUM_LEDS, paletteIndex, density);
  }

  FastLED.delay(speed);
  paletteIndex++;
  FastLED.setBrightness(brightness);
}

