#pragma once

#define FASTLED_INTERNAL
#include <FastLED.h>

DEFINE_GRADIENT_PALETTE (sunset1_gp) {
  0, 90, 206, 198, // Teal
  51, 232, 131, 97, // Peach
  102, 242, 113, 78, // Orange
  180, 234, 65, 152, // Pink
  255, 124, 44, 92 // Purple
};

DEFINE_GRADIENT_PALETTE (sunset2_gp) {
  0, 181, 61, 173, // Lavender
  170, 216, 71, 98, // Peach
  255, 249, 123, 64// Orange
};

DEFINE_GRADIENT_PALETTE (sanjaun_gp) {
  0, 99, 168, 211, // Teal
  51, 221, 139, 146, // Pinkish gray
  102, 126, 106, 168, // Bluish gray
  180, 77, 137, 137, // Pale teal
  255, 22, 78, 79
};

DEFINE_GRADIENT_PALETTE (fire_gp) {
  0, 49, 22, 21,  // Dark Red
  51, 103, 35, 21,
  120, 163, 55, 23,
  200, 224, 100, 22,
  255, 253, 150, 23
};

DEFINE_GRADIENT_PALETTE (outrun1_gp) {
  0, 192, 6, 172, // Purple 1
  37, 160, 7, 182, // Purple 2
  74, 99, 49, 192, // Purple 
  105, 75, 69, 191, //Purple blue
  136, 20, 109, 197, //Blue 1
  167, 14, 144, 206, // Blue 2
  255, 9, 170, 204   // Blue 3
};

DEFINE_GRADIENT_PALETTE (outrun2_gp) {
  0, 94, 49, 150, // Purple
  75, 34, 91, 170, // Blue
  140, 248, 190, 21, // Yellow
  200, 242, 93, 50, // Orange
  255, 252, 21, 128, // Pink
};

DEFINE_GRADIENT_PALETTE (outrun3_gp) {
  0, 139, 242, 238, // Teal
  125, 223, 115, 198, // Pink
  255, 165, 90, 247 // Purple 
};

CRGBPalette16 sunset1 = sunset1_gp;
CRGBPalette16 sunset2 = sunset2_gp;
CRGBPalette16 sanjaun = sanjaun_gp;
CRGBPalette16 fire = fire_gp;
CRGBPalette16 outrun1 = outrun1_gp;
CRGBPalette16 outrun2 = outrun2_gp;
CRGBPalette16 outrun3 = outrun3_gp;
