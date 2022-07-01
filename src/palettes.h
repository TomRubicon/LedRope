#pragma once

#define FASTLED_INTERNAL
#include <FastLED.h>

DEFINE_GRADIENT_PALETTE (sunset1_gp) {
  0, 136, 205, 200, // Teal
  51, 233, 178, 159, // Peach
  102, 254, 153, 127, // Orange
  180, 237, 117, 179, // Pink
  255, 135, 98, 120 // Purple
};

CRGBPalette16 sunset1 = sunset1_gp;
