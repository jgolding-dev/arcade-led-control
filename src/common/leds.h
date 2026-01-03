#ifndef leds_h
  #define leds_h

  // Make FastLED library compatible
  // #define FASTLED_RP2040_CLOCKLESS_M0_FALLBACK 0

  // -------- Physical Pins -------- //
  
  #define OPTIONS_PIN_R 16
  #define OPTIONS_PIN_G 18
  #define OPTIONS_PIN_B 20
  #define KAIMANA_DATA_PIN 3 // Player1 & Player2 buttons
  #define BACKLIGHT_DATA_PIN 7

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

  #define BACKLIGHT_1 0
  #define BACKLIGHT_2 1
  #define BACKLIGHT_3 2

  // -------- Digital LED Chip Types -------- //

  #define PLAYER1_LED_TYPE   WS2812B
  #define PLAYER2_LED_TYPE   WS2812B
  #define BACKLIGHT_LED_TYPE WS2811

  #define COLOR_ORDER GRB // Color order (RGB, GRB, etc.)

  // -------- Digital LED Counts -------- //

  #define PLAYER1_LED_COUNT   16
  #define PLAYER2_LED_COUNT   16
  #define BACKLIGHT_LED_COUNT 3  // We actually have 300 backlight LEDs, but they're
  //                                split into 3 addressable LED sections. So, as far
  //                                as our program is concerned, we have only have 3.

  #define LED_ZONES_COUNT 5

  // -------- LED Groups -------- //

  const int OPTIONS_LEDS[] = {
    OPTIONS_PIN_R,
    OPTIONS_PIN_G,
    OPTIONS_PIN_B
  };

  const int PLAYER1_LEDS[] = {
    PLAYER1_BTN1,
    PLAYER1_BTN2,
    PLAYER1_BTN3,
    PLAYER1_BTN4,
    PLAYER1_BTN5,
    PLAYER1_BTN6,
    PLAYER1_BTN7,
    PLAYER1_BTN8,
    // PLAYER1_JOYSTICK
  };

  const int PLAYER2_LEDS[] = {
    PLAYER2_BTN1,
    PLAYER2_BTN2,
    PLAYER2_BTN3,
    PLAYER2_BTN4,
    PLAYER2_BTN5,
    PLAYER2_BTN6,
    PLAYER2_BTN7,
    PLAYER2_BTN8,
    // PLAYER2_JOYSTICK
  };

  const int BACKLIGHT_LEDS[] = {
    BACKLIGHT_1,
    BACKLIGHT_2,
    BACKLIGHT_3
  };

  class Leds {
    public:
      static void initPins() {
        pinMode(OPTIONS_PIN_R, OUTPUT);
        pinMode(OPTIONS_PIN_G, OUTPUT);
        pinMode(OPTIONS_PIN_B, OUTPUT);
        pinMode(KAIMANA_DATA_PIN, OUTPUT);
        pinMode(BACKLIGHT_DATA_PIN, OUTPUT);
      }
  };

#endif