#ifndef pins_h
#define pins_h

#include <Arduino.h>

// ---------------- Output ---------------- //

#define ACCENT_DATA_PIN                 17

#define PLAYER1_BALLTOP_DATA_PIN        16
#define PLAYER1_JOYSTICK_DATA_PIN       18
#define PLAYER1_BUTTONS_DATA_PIN        19

#define PLAYER2_BUTTONS_DATA_PIN        20
#define PLAYER2_JOYSTICK_DATA_PIN       22
#define PLAYER2_BALLTOP_DATA_PIN        26

#define OPTIONS_PIN_R                   21
#define OPTIONS_PIN_G                   27
#define OPTIONS_PIN_B                   28



// ---------------- Input ---------------- //

#define P1_BUTTON_PRESS_PIN             0
#define P1_JOYSTICK_LEFT_PIN            1
#define P1_JOYSTICK_UP_PIN              2
#define P1_JOYSTICK_RIGHT_PIN           3
#define P1_JOYSTICK_DOWN_PIN            4

#define OPTIONS_BUTTON_PRESS_PIN        5

#define P2_BUTTON_PRESS_PIN             6
#define P2_JOYSTICK_DOWN_PIN            7
#define P2_JOYSTICK_UP_PIN              8
#define P2_JOYSTICK_LEFT_PIN            9
#define P2_JOYSTICK_RIGHT_PIN           10

#define MACRO_1_PIN                     11
#define MACRO_2_PIN                     12
#define MACRO_3_PIN                     13
#define MACRO_4_PIN                     14

#define ACTIVITY_PIN                    15 // TODO: Remove, and implicitly check for activity instead

// ---------------- Groups ---------------- //

const int OPTIONS_LED_PINS[] = {
  OPTIONS_PIN_R,
  OPTIONS_PIN_G,
  OPTIONS_PIN_B
};

class Pins {
public:
  static void initPins() {
    // Options
    pinMode(OPTIONS_PIN_R, OUTPUT);
    pinMode(OPTIONS_PIN_G, OUTPUT);
    pinMode(OPTIONS_PIN_B, OUTPUT);

    // Player 1
    pinMode(PLAYER1_BUTTONS_DATA_PIN, OUTPUT);
    pinMode(PLAYER1_JOYSTICK_DATA_PIN, OUTPUT);
    pinMode(PLAYER1_BALLTOP_DATA_PIN, OUTPUT);

    // Player 2
    pinMode(PLAYER2_BUTTONS_DATA_PIN, OUTPUT);
    pinMode(PLAYER2_JOYSTICK_DATA_PIN, OUTPUT);
    pinMode(PLAYER2_BALLTOP_DATA_PIN, OUTPUT);

    // Accent Lighting
    pinMode(ACCENT_DATA_PIN, OUTPUT);

    // Activity Inputs
    pinMode(P1_BUTTON_PRESS_PIN, INPUT_PULLDOWN);
    pinMode(P1_JOYSTICK_DOWN_PIN, INPUT_PULLDOWN);
    pinMode(P1_JOYSTICK_UP_PIN, INPUT_PULLDOWN);
    pinMode(P1_JOYSTICK_LEFT_PIN, INPUT_PULLDOWN);
    pinMode(P1_JOYSTICK_RIGHT_PIN, INPUT_PULLDOWN);

    pinMode(OPTIONS_BUTTON_PRESS_PIN, INPUT_PULLDOWN);

    pinMode(P2_BUTTON_PRESS_PIN, INPUT_PULLDOWN);
    pinMode(P2_JOYSTICK_DOWN_PIN, INPUT_PULLDOWN);
    pinMode(P2_JOYSTICK_UP_PIN, INPUT_PULLDOWN);
    pinMode(P2_JOYSTICK_LEFT_PIN, INPUT_PULLDOWN);
    pinMode(P2_JOYSTICK_RIGHT_PIN, INPUT_PULLDOWN);

    pinMode(MACRO_1_PIN, INPUT_PULLDOWN);
    pinMode(MACRO_2_PIN, INPUT_PULLDOWN);
    pinMode(MACRO_3_PIN, INPUT_PULLDOWN);
    pinMode(MACRO_4_PIN, INPUT_PULLDOWN);

    pinMode(ACTIVITY_PIN, INPUT_PULLDOWN);
  }
};

#endif