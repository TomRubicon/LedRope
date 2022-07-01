#include <Arduino.h>
#include <AiEsp32RotaryEncoder.h>
#include <Encoder.h>
#include <OneButton.h>

#define ROTARY_ENCODER_A_PIN 32
#define ROTARY_ENCODER_B_PIN 33
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENOCDER_STEPS 5

/* #define encPinA 32 */
/* #define encPinB 33 */
#define encBtn 27

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
/* int encoderPos = 0; */

/* Encoder enc(14, 12); */

/* int valRotary, lastValRotary; */

/* void doEncoder() { */
/*   Serial.println("doEncoder() fired"); */
/*   if (digitalRead(encPinA) == digitalRead(encPinB)) { */
/*     encoderPos++; */
/*   } else { */
/*     encoderPos--; */
/*   } */
/*   valRotary = encoderPos/2.5; */
/* } */

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
  Serial.begin(115200);
  Serial.println("Started sketch");
  /* pinMode(encPinA, INPUT_PULLUP); */
  /* pinMode(encPinB, INPUT_PULLUP); */
  /* pinMode(encBtn, INPUT_PULLUP); */
  /* attachInterrupt(encPinA, doEncoder, CHANGE); */
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);

  bool circleValues = false;
  rotaryEncoder.setBoundaries(0, 1000, circleValues);
  rotaryEncoder.setAcceleration(250);

  btn.attachClick(handleClick);
  btn.attachDoubleClick(handleDoubleClick);
  btn.attachLongPressStart(handleLongClick);
}

long oldPosition = -999;

void loop() {
  /* long newPosition = enc.read(); */
  /* if (newPosition != oldPosition) { */
  /*   oldPosition = newPosition; */
  /*   Serial.println(newPosition); */
  /* } */
  rotary_loop();
  btn.tick();
  /* if(valRotary > lastValRotary) { */
  /*   Serial.print(valRotary); */
  /*   Serial.print(" CW"); */
  /*   Serial.println(" "); */
  /* } */
  /* if(valRotary < lastValRotary) { */
  /*   Serial.print(valRotary); */
  /*   Serial.print(" CCW"); */
  /*   Serial.println(" "); */
  /* } */
  /* lastValRotary = valRotary; */
}

