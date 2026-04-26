#pragma once

#include <Arduino.h>

enum LedButtonIndex : uint8_t {
  B1_LED              = 8,
  B2_LED              = 10,
  B3_LED              = 6,
  B4_LED              = 4,
  L1_LED              = 0,
  R1_LED              = 2,
  L2_LED              = 14,
  R2_LED              = 12
};

enum LedJoystickIndex : uint8_t {
  JOY_UP_LED          = 0,
  JOY_UP_RIGHT_LED    = 1,
  JOY_RIGHT_LED       = 2,
  JOY_DOWN_RIGHT_LED  = 3,
  JOY_DOWN_LED        = 4,
  JOY_DOWN_LEFT_LED   = 5,
  JOY_LEFT_LED        = 6,
  JOY_UP_LEFT_LED     = 7,
  JOY_BALLTOP_LED     = 8
};  

enum OptionsLedIndex: uint8_t {
  HOME_LED            = 0,
  P1_SELECT_LED       = 1,
  P1_START_LED        = 2,
  P2_SELECT_LED       = 3,
  P2_START_LED        = 4
};

// -------- LED Chip Types -------- //
#define ACCENT_LED_TYPE                   WS2811
#define PLAYER1_BUTTONS_LED_TYPE          WS2812B
#define PLAYER1_JOYSTICK_LED_TYPE         WS2812B
#define PLAYER2_BUTTONS_LED_TYPE          WS2812B
#define PLAYER2_JOYSTICK_LED_TYPE         WS2812B
#define OPTIONS_BUTTONS_LED_TYPE          WS2812B

// -------- Counts -------- //

#define OPTIONS_BUTTONS_LED_COUNT         5
#define PLAYER1_BUTTONS_LED_COUNT         16
#define PLAYER1_JOYSTICK_LED_COUNT        9
#define PLAYER2_BUTTONS_LED_COUNT         16
#define PLAYER2_JOYSTICK_LED_COUNT        9
#define ACCENT_LED_COUNT                  100  // We actually have 300 backlight LEDs, but they're
//                                              split into 1 IC per 3 LEDs. So, as far as our
//                                              program is concerned, we have 100.

#define COLOR_ORDER GRB  // Color order (RGB, GRB, etc.)