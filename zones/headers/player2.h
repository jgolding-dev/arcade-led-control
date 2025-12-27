#ifndef player1_h
#define player1_h
#endif

#include "zone.h"
#include "../../common/leds.h"

const int LEDS[] = {
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

const ANIMATION_TYPE ANIMATION_TYPES[] = {    
    STATIC,
    // COLOR_SHIFT,
    FADE,
    // PULSE,
    OFF
};

class Player2 : public Zone {
  public:
    Player2::Player2(const int* _leds, const ANIMATION_TYPE animationTypes)
}