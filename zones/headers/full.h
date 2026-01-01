#ifndef full_h
#define full_h
#endif

#include "zone.h"
#include "../../common/leds.h"

const int LEDS[] = {
  OPTIONS_LED_R,
  OPTIONS_LED_G,
  OPTIONS_LED_B,
  PLAYER1_BTN1,
  PLAYER1_BTN2,
  PLAYER1_BTN3,
  PLAYER1_BTN4,
  PLAYER1_BTN5,
  PLAYER1_BTN6,
  PLAYER1_BTN7,
  PLAYER1_BTN8,
  PLAYER2_BTN1,
  PLAYER2_BTN2,
  PLAYER2_BTN3,
  PLAYER2_BTN4,
  PLAYER2_BTN5,
  PLAYER2_BTN6,
  PLAYER2_BTN7,
  PLAYER2_BTN8,
};

const ANIMATION_TYPE ANIMATION_TYPES[] = {   
    // CUSTOM, 
    STATIC,
    // COLOR_SHIFT,
    FADE,
    // PULSE,
    OFF
};

class Full : public Zone {
  public:
    Full::Full() {
      ledPins* = LEDS;
      animationTypes = ANIMATION_TYPES;
    }
  private:
    _lastAnimStepMs;
    _fadeStepMs;
    _fadeColorIndex;
    _fadePercent;
    _fadeDir;
};