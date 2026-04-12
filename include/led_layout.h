#ifndef led_layout_h
#define led_layout_h

#include <Arduino.h>

enum Player1LedButtonIndex : uint8_t {
  P1_BTN1 = 8,
  P1_BTN2 = 10,
  P1_BTN3 = 6,
  P1_BTN4 = 4,
  P1_L1 = 0,
  P1_R1 = 2,
  P1_L2 = 14,
  P1_R2 = 12
};

enum Player1LedJoystickIndex : uint8_t {
  P1_UP         = 0,
  P1_UP_RIGHT   = 1,
  P1_RIGHT      = 2,
  P1_DOWN_RIGHT = 3,
  P1_DOWN       = 4,
  P1_DOWN_LEFT  = 5,
  P1_LEFT       = 6,
  P1_UP_LEFT    = 7,
  P1_BALLTOP    = 8
};

enum Player2LedButtonIndex : uint8_t {
  P2_BTN1 = 8,
  P2_BTN2 = 10,
  P2_BTN3 = 6,
  P2_BTN4 = 4,
  P2_L1 = 0,
  P2_R1 = 2,
  P2_L2 = 14,
  P2_R2 = 12
};

enum Player2LedJoystickIndex : uint8_t {
  P2_UP         = 0,
  P2_UP_RIGHT   = 1,
  P2_RIGHT      = 2,
  P2_DOWN_RIGHT = 3,
  P2_DOWN       = 4,
  P2_DOWN_LEFT  = 5,
  P2_LEFT       = 6,
  P2_UP_LEFT    = 7,
  P2_BALLTOP    = 8
};

enum OptionsLedIndex: uint8_t {
  OP_P1_HOME = 0,
  OP_P1_SELECT = 1,
  OP_P1_START = 2,
  OP_P2_START = 3,
  OP_P2_SELECT = 4
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

#endif