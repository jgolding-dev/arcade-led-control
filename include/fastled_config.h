#pragma once

#ifndef fastled_config_h
#define fastled_config_h

#define FASTLED_RP2040_CLOCKLESS_M0_FALLBACK 0
#define FASTLED_RP2040_CLOCKLESS_PIO 1

#define NUM_COLORS 9

#include <Arduino.h>
#include <FastLED.h>

// RGB value structure.
typedef struct __attribute__ ((__packed__)) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB_t;

const RGB_t RGB_BLACK        = {000,000,000};
const RGB_t RGB_BLUE         = {000,000,255};
const RGB_t RGB_BLUE_VIOLET  = {138, 43, 226};
const RGB_t RGB_MAGENTA      = {255, 0, 255};
const RGB_t RGB_WHITE        = {255, 255, 255};
const RGB_t RGB_RED          = {255, 0, 0};
const RGB_t RGB_ORANGE       = {255, 165, 0};
const RGB_t RGB_YELLOW       = {255, 255, 0};
const RGB_t RGB_GREEN        = {0, 255, 0};
const RGB_t RGB_CYAN         = {0, 255, 255};

const RGB_t COLORS[NUM_COLORS] = {
  RGB_BLUE,
  RGB_BLUE_VIOLET,
  RGB_MAGENTA,
  RGB_WHITE,
  RGB_RED,
  RGB_ORANGE,
  RGB_YELLOW,
  RGB_GREEN,
  RGB_CYAN
};

const CRGBPalette16 COLOR_PALETTE = CRGBPalette16(
  CRGB::Blue, CRGB::Blue,
  CRGB::BlueViolet, CRGB::BlueViolet,
  CRGB::Red, CRGB::Red,
  CRGB::Orange, CRGB::Orange,
  CRGB::Yellow, CRGB::Yellow,
  CRGB::Green, CRGB::Green,
  CRGB::Cyan, CRGB::Cyan,
  CRGB::Blue, CRGB::Blue  // Loops back to the beginning
);

#endif