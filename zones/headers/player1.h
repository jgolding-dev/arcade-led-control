#ifndef player1_h;
#define player1_h;
#endif

#include "zone.h"
#include "../../common/leds.h"

const int LEDS[] = {
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

const ANIMATION_TYPE ANIMATION_TYPES[] = {    
    STATIC,
    // COLOR_SHIFT,
    FADE,
    // PULSE,
    OFF
};

class Player1 : public Zone {
  public:
    Player1::Player1(const int* _leds, const ANIMATION_TYPE animationTypes)
}