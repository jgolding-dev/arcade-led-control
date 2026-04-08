#ifndef pins_h
#define pins_h

#include <Arduino.h>

// ---------------- Output ---------------- //

#define ACCENT_DATA_PIN                   18
#define OPTIONS_BUTTONS_DATA_PIN          19

#define PLAYER1_BUTTONS_DATA_PIN          16
#define PLAYER1_JOYSTICK_DATA_PIN         17

#define P1_LS_MODE_PIN                    20
#define P1_DP_MODE_PIN                    22
#define P1_RS_MODE_PIN                    26

#define PLAYER2_BUTTONS_DATA_PIN          28
#define PLAYER2_JOYSTICK_DATA_PIN         27     

#define REC_BUTTON_LED_PIN                6
#define P2_LS_MODE_PIN                    7
#define P2_DP_MODE_PIN                    8
#define P2_RS_MODE_PIN                    9

// ---------------- Input ---------------- //

#define P1_ACTIVITY_PIN                   0
#define DISPLAY_CLK_PIN                   1
#define DISPLAY_MOSI_PIN                  2
#define DISPLAY_X_PIN                     3

#define ROTARY_XX_PIN                     11
#define ROTARY_X_PIN                      12
#define ROTARY_CLK_PIN                    13
#define DISPLAY_X_PIN                     14

#define P2_ACTIVITY_PIN                   15

// ---------------- Groups ---------------- //

class Pins {
public:
  static void initPins() {
    // Options
    pinMode(OPTIONS_BUTTONS_DATA_PIN, OUTPUT);


    // Player 1
    pinMode(PLAYER1_BUTTONS_DATA_PIN, OUTPUT);
    pinMode(PLAYER1_JOYSTICK_DATA_PIN, OUTPUT);

    // Player 2
    pinMode(PLAYER2_BUTTONS_DATA_PIN, OUTPUT);
    pinMode(PLAYER2_JOYSTICK_DATA_PIN, OUTPUT);

    // Joystick Modes
    pinMode(P1_LS_MODE_PIN, OUTPUT);
    pinMode(P1_DP_MODE_PIN, OUTPUT);
    pinMode(P1_RS_MODE_PIN, OUTPUT);
    pinMode(P2_LS_MODE_PIN, OUTPUT);
    pinMode(P2_DP_MODE_PIN, OUTPUT);
    pinMode(P2_RS_MODE_PIN, OUTPUT);

    // Accent Lighting
    pinMode(ACCENT_DATA_PIN, OUTPUT);

    // Inputs
    pinMode(P1_ACTIVITY_PIN, INPUT_PULLDOWN);
    pinMode(P2_ACTIVITY_PIN, INPUT_PULLDOWN);
    pinMode(DISPLAY_CLK_PIN, INPUT_PULLDOWN);
    pinMode(DISPLAY_MOSI_PIN, INPUT_PULLDOWN);
    pinMode(DISPLAY_X_PIN, INPUT_PULLDOWN);

    pinMode(ROTARY_XX_PIN, INPUT_PULLDOWN);
    pinMode(ROTARY_X_PIN, INPUT_PULLDOWN);
    pinMode(ROTARY_CLK_PIN, INPUT_PULLDOWN);
    pinMode(DISPLAY_X_PIN, INPUT_PULLDOWN);
  }
};

#endif