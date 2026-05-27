#pragma once

#ifndef fastled_config_h
#define fastled_config_h

#define FASTLED_RP2040_CLOCKLESS_M0_FALLBACK 0
#define FASTLED_RP2040_CLOCKLESS_PIO 1

#define NUM_COLORS 9

#include <Arduino.h>
#include <FastLED.h>

const CRGB BLACK   = CRGB::Black;
const CRGB BLUE    = CRGB::Blue;
const CRGB RED     = CRGB::Red;
const CRGB GREEN   = CRGB::Green;
const CRGB YELLOW  = CRGB::Yellow;
const CRGB PURPLE  = CRGB::Purple;
const CRGB CYAN    = CRGB::Cyan;
const CRGB WHITE   = CRGB::White;
const CRGB GOLD    = CRGB::Gold;
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