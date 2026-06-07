#ifndef led_layout_h
#define led_layout_h

#include <Arduino.h>

#define SINGLE_BTN_LED_COUNT 2
#define SINGLE_OPTIONS_BTN_LED_COUNT 1
#define JOY_DIRECTION_LED_COUNT 4
#define JOY_BALLTOP_LED_COUNT 1

// ----------------- Main Buttons ----------------- //
const uint8_t BTN1_LEDs[] = {8, 9};
const uint8_t BTN2_LEDs[] = {10, 11};
const uint8_t BTN3_LEDs[] = {6, 7};
const uint8_t BTN4_LEDs[] = {4, 5};
const uint8_t L1_LEDs[] = {0, 1};
const uint8_t R1_LEDs[] = {2, 3};
const uint8_t L2_LEDs[] = {14, 15};
const uint8_t R2_LEDs[] = {12, 13};

// ----------------- Options Buttons ----------------- //
const uint8_t P1_SELECT_LEDs[] = {2};
const uint8_t P1_START_LEDs[] = {3};
const uint8_t P2_SELECT_LEDs[] = {4};
const uint8_t P2_START_LEDs[] = {5};
const uint8_t HOME_LEDs[] = {1};
const uint8_t EXTRA1_LEDs[] = {0};

// ----------------- Joystick ----------------- //
const uint8_t JOY_UP_LEDs[] = {14, 15, 0, 1};
const uint8_t JOY_UP_RIGHT_LEDs[] = {0, 1, 2, 3};
const uint8_t JOY_RIGHT_LEDs[] = {2, 3, 4, 5};
const uint8_t JOY_DOWN_RIGHT_LEDs[] = {4, 5, 6, 7};
const uint8_t JOY_DOWN_LEDs[] = {6, 7, 8, 9};
const uint8_t JOY_DOWN_LEFT_LEDs[] = {8, 9, 10, 11};
const uint8_t JOY_LEFT_LEDs[] = {10, 11, 12, 13};
const uint8_t JOY_UP_LEFT_LEDs[] = {12, 13, 14, 15};
const uint8_t JOY_BALLTOP_LEDs[] = {16};

// -------- LED Chip Types -------- //
#define ACCENT_LED_TYPE                   WS2811
#define PLAYER1_BUTTONS_LED_TYPE          WS2812B
#define PLAYER1_JOYSTICK_LED_TYPE         WS2812B
#define PLAYER2_BUTTONS_LED_TYPE          WS2812B
#define PLAYER2_JOYSTICK_LED_TYPE         WS2812B
#define OPTIONS_BUTTONS_LED_TYPE          WS2812B

// -------- Counts -------- //
#define OPTIONS_BUTTONS_LED_COUNT         6
#define PLAYER1_BUTTONS_LED_COUNT         16
#define PLAYER1_JOYSTICK_LED_COUNT        17
#define PLAYER2_BUTTONS_LED_COUNT         16
#define PLAYER2_JOYSTICK_LED_COUNT        17
#define ACCENT_LED_COUNT                  100  // We actually have 300 backlight LEDs, but they're
//                                              split into 1 IC per 3 LEDs. So, as far as our
//                                              program is concerned, we have 100.

#endif