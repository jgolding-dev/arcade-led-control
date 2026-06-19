#ifndef led_layout_h
#define led_layout_h

#include <Arduino.h>

// -------- LED Chip Types -------- //
#define ACCENT_LED_TYPE                   WS2811
#define ACTION_BUTTONS_LED_TYPE           WS2812B
#define JOY_LED_TYPE                 WS2812B
#define OPTIONS_BUTTONS_LED_TYPE          WS2812B

// -------- LED Color Order -------- //
#define ACCENT_LED_COLOR_ORDER            GRB
#define ACTION_BUTTONS_LED_COLOR_ORDER    GRB
#define JOY_LED_COLOR_ORDER          GRB
#define OPTIONS_BUTTONS_LED_COLOR_ORDER   GRB

// -------- LED Counts Per Button -------- //
const uint8_t ACTION_BTN_LED_COUNT          = 4; // Each action button has 4 LEDs
const uint8_t OPTIONS_BTN_LED_COUNT         = 1;
const uint8_t JOY_DIRECTION_LED_COUNT       = 4;

// -------- Buttons Counts (Per Zone) -------- //
const uint8_t ACTION_BTN_COUNT              = 8;
const uint8_t OPTIONS_BTN_COUNT             = 6;

// -------- Total LED Counts (Per Zone) -------- //
const uint8_t ACTION_LED_ZONE_COUNT         = ACTION_BTN_LED_COUNT * ACTION_BTN_COUNT;
const uint8_t OPTIONS_LED_ZONE_COUNT        = OPTIONS_BTN_LED_COUNT * OPTIONS_BTN_COUNT;
const uint8_t JOY_RING_LED_COUNT       = (JOY_DIRECTION_LED_COUNT * 4); // A joystick has 4 directions
const uint8_t JOY_BALLTOP_LED_COUNT    = 1;
const uint8_t JOY_LED_ZONE_COUNT       = JOY_RING_LED_COUNT + JOY_BALLTOP_LED_COUNT;
const uint8_t ACCENT_LED_ZONE_COUNT         = 100;      // We actually have 300 backlight LEDs, but they're
//                                                         split into 1 IC per 3 LEDs. So, as far as our
//                                                         program is concerned, we have 100.

// ----------------- Main Buttons ----------------- //
const uint8_t BTN1_LEDs[ACTION_BTN_LED_COUNT] = {28, 29, 30, 31};
const uint8_t BTN2_LEDs[ACTION_BTN_LED_COUNT] = {20, 21, 22, 23};
const uint8_t BTN3_LEDs[ACTION_BTN_LED_COUNT] = {24, 25, 26, 27};
const uint8_t BTN4_LEDs[ACTION_BTN_LED_COUNT] = {16, 17, 18, 19};
const uint8_t L1_LEDs[ACTION_BTN_LED_COUNT] = {0, 1, 2, 3};
const uint8_t R1_LEDs[ACTION_BTN_LED_COUNT] = {8, 9, 10, 11};

const uint8_t L2_LEDs[ACTION_BTN_LED_COUNT] = {4, 5, 6, 7};
const uint8_t R2_LEDs[ACTION_BTN_LED_COUNT] = {12, 13, 14, 15};

// ----------------- Options Buttons ----------------- //
const uint8_t P1_SELECT_LEDs[OPTIONS_BTN_LED_COUNT] = {2};
const uint8_t P1_START_LEDs[OPTIONS_BTN_LED_COUNT] = {3};
const uint8_t P2_SELECT_LEDs[OPTIONS_BTN_LED_COUNT] = {4};
const uint8_t P2_START_LEDs[OPTIONS_BTN_LED_COUNT] = {5};
const uint8_t HOME_LEDs[OPTIONS_BTN_LED_COUNT] = {1};
const uint8_t EXTRA1_LEDs[OPTIONS_BTN_LED_COUNT] = {0};

// ----------------- Joystick ----------------- //
const uint8_t JOY_UP_LEDs[JOY_DIRECTION_LED_COUNT] = {14, 15, 0, 1};
const uint8_t JOY_UP_RIGHT_LEDs[JOY_DIRECTION_LED_COUNT] = {0, 1, 2, 3};
const uint8_t JOY_RIGHT_LEDs[JOY_DIRECTION_LED_COUNT] = {2, 3, 4, 5};
const uint8_t JOY_DOWN_RIGHT_LEDs[JOY_DIRECTION_LED_COUNT] = {4, 5, 6, 7};
const uint8_t JOY_DOWN_LEDs[JOY_DIRECTION_LED_COUNT] = {6, 7, 8, 9};
const uint8_t JOY_DOWN_LEFT_LEDs[JOY_DIRECTION_LED_COUNT] = {8, 9, 10, 11};
const uint8_t JOY_LEFT_LEDs[JOY_DIRECTION_LED_COUNT] = {10, 11, 12, 13};
const uint8_t JOY_UP_LEFT_LEDs[JOY_DIRECTION_LED_COUNT] = {12, 13, 14, 15};
const uint8_t JOY_BALLTOP_LEDs[JOY_BALLTOP_LED_COUNT] = {16};

#endif