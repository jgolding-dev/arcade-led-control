#ifndef led_layout_h
#define led_layout_h

#include <Arduino.h>

enum Player1LedButtonIndex : uint8_t {
  P1_BTN1 = 0,
  P1_BTN2 = 2,
  P1_BTN3 = 4,
  P1_BTN4 = 6,
  P1_BTN5 = 8,
  P1_BTN6 = 10,
  P1_BTN7 = 12,
  P1_BTN8 = 14
};

enum Player1LedJoystickIndex : uint8_t {
  P1_UP         = 0,
  P1_UP_RIGHT   = 1,
  P1_RIGHT      = 2,
  P1_DOWN_RIGHT = 3,
  P1_DOWN       = 4,
  P1_DOWN_LEFT  = 5,
  P1_LEFT       = 6,
  P1_UP_LEFT    = 7
};

enum Player2LedButtonIndex : uint8_t {
  P2_BTN1 = 0,
  P2_BTN2 = 2,
  P2_BTN3 = 4,
  P2_BTN4 = 6,
  P2_BTN5 = 8,
  P2_BTN6 = 10,
  P2_BTN7 = 12,
  P2_BTN8 = 14
};

enum Player2LedJoystickIndex : uint8_t {
  P2_UP         = 0,
  P2_UP_RIGHT   = 1,
  P2_RIGHT      = 2,
  P2_DOWN_RIGHT = 3,
  P2_DOWN       = 4,
  P2_DOWN_LEFT  = 5,
  P2_LEFT       = 6,
  P2_UP_LEFT    = 7
};

#define PLAYER2_BTN1 0
#define PLAYER2_BTN2 2
#define PLAYER2_BTN3 4
#define PLAYER2_BTN4 6
#define PLAYER2_BTN5 8
#define PLAYER2_BTN6 10
#define PLAYER2_BTN7 12
#define PLAYER2_BTN8 14

// -------- LED Chip Types -------- //
#define ACCENT_LED_TYPE                   WS2811
#define PLAYER1_BUTTONS_LED_TYPE          WS2812B
#define PLAYER1_JOYSTICK_LED_TYPE         WS2812B
#define PLAYER1_BALLTOP_LED_TYPE          WS2812B
#define PLAYER2_BUTTONS_LED_TYPE          WS2812B
#define PLAYER2_JOYSTICK_LED_TYPE         WS2812B
#define PLAYER2_BALLTOP_LED_TYPE          WS2812B

// -------- Counts -------- //

#define OPTIONS_LED_COUNT                 3
#define PLAYER1_BUTTONS_LED_COUNT         16
#define PLAYER1_JOYSTICK_LED_COUNT   8
#define PLAYER1_BALLTOP_LED_COUNT         1
#define PLAYER2_BUTTONS_LED_COUNT         16
#define PLAYER2_JOYSTICK_LED_COUNT   8
#define PLAYER2_BALLTOP_LED_COUNT         1
#define ACCENT_LED_COUNT                  100  // We actually have 300 backlight LEDs, but they're
//                                              split into 1 IC per 3 LEDs. So, as far as our
//                                              program is concerned, we have 100.

#define COLOR_ORDER GRB  // Color order (RGB, GRB, etc.)

#endif