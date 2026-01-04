#ifndef leds_h
#define leds_h

// -------- Physical Pins -------- //

#define OPTIONS_PIN_R      16
#define OPTIONS_PIN_G      18
#define OPTIONS_PIN_B      20
#define PLAYER1_DATA_PIN   14
#define PLAYER2_DATA_PIN   12
#define BACKLIGHT_DATA_PIN 10

// -------- Digital Pins -------- //

#define PLAYER1_BTN1 0
#define PLAYER1_BTN2 2
#define PLAYER1_BTN3 4
#define PLAYER1_BTN4 6
#define PLAYER1_BTN5 8
#define PLAYER1_BTN6 10
#define PLAYER1_BTN7 12
#define PLAYER1_BTN8 14
// #define PLAYER1_JOYSTICK 16;

#define PLAYER2_BTN1 0
#define PLAYER2_BTN2 2
#define PLAYER2_BTN3 4
#define PLAYER2_BTN4 6
#define PLAYER2_BTN5 8
#define PLAYER2_BTN6 10
#define PLAYER2_BTN7 12
#define PLAYER2_BTN8 14
// #define PLAYER2_JOYSTICK 16;

// -------- Digital LED Chip Types -------- //

#define PLAYER1_LED_TYPE   WS2812B
#define PLAYER2_LED_TYPE   WS2812B
#define BACKLIGHT_LED_TYPE WS2811

#define COLOR_ORDER GRB  // Color order (RGB, GRB, etc.)

// -------- Counts -------- //

#define OPTIONS_LED_COUNT   3
#define PLAYER1_LED_COUNT   16
#define PLAYER2_LED_COUNT   16
#define BACKLIGHT_LED_COUNT 100  // We actually have 300 backlight LEDs, but they're
//                                  split into 1 IC per 3 LEDs. So, as far as our
//                                  program is concerned, we have 100.

// -------- LED Groups -------- //

const int OPTIONS_LEDS[OPTIONS_LED_COUNT] = {
  OPTIONS_PIN_R,
  OPTIONS_PIN_G,
  OPTIONS_PIN_B
};

class Leds {
public:
  static void initPins() {
    pinMode(OPTIONS_PIN_R, OUTPUT);
    pinMode(OPTIONS_PIN_G, OUTPUT);
    pinMode(OPTIONS_PIN_B, OUTPUT);
    pinMode(PLAYER1_DATA_PIN, OUTPUT);
    pinMode(PLAYER2_DATA_PIN, OUTPUT);
    pinMode(BACKLIGHT_DATA_PIN, OUTPUT);
  }
};

#endif