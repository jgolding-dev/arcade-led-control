#pragma once

#ifndef fastled_config_h
#define fastled_config_h

#define FASTLED_RP2040_CLOCKLESS_M0_FALLBACK 0
#define FASTLED_RP2040_CLOCKLESS_PIO 1

#define NUM_COLORS 9

#include <Arduino.h>

// RGB value structure.
typedef struct __attribute__ ((__packed__)) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB_t;

const RGB_t BLACK   = {000,000,000};
const RGB_t BLUE    = {000,000,255};
const RGB_t RED     = {255,000,000};
const RGB_t GREEN   = {000,255,000};
const RGB_t YELLOW  = {255,255,000};
const RGB_t PURPLE  = {255,000,255};
const RGB_t CYAN    = {000,255,255};
const RGB_t WHITE   = {255,255,255};
const RGB_t GOLD    = {255,150,000};

const RGB_t STATIC_COLORS[NUM_COLORS] = {
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