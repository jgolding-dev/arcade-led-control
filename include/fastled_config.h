#pragma once

#ifndef fastled_config_h
#define fastled_config_h

#define FASTLED_RP2040_CLOCKLESS_M0_FALLBACK 0
#define FASTLED_RP2040_CLOCKLESS_PIO 1

#define NUM_COLORS 9

#include <Arduino.h>
#include <FastLED.h>

// RGB value structure.
// typedef struct __attribute__ ((__packed__)) {
//     uint8_t r;
//     uint8_t g;
//     uint8_t b;
// } RGB_t;

const CRGB BLACK   = CRGB::BLACK;
const CRGB BLUE    = CRGB::BLUE;
const CRGB RED     = CRGB::RED;
const CRGB GREEN   = CRGB::GREEN;
const CRGB YELLOW  = CRGB::YELLOW
const CRGB PURPLE  = CRGB::PURPLE;
const CRGB CYAN    = CRGB::CYAN;
const CRGB WHITE   = CRGB::WHITE;
const CRGB GOLD    = CRGB::GOLD;
const CRGB STATIC_COLORS[NUM_COLORS] = {
  BLUE,
  RED,
  GREEN,
  PURPLE,
  YELLOW,
  CYAN,
  GOLD,
  WHITE
};

#endif