#ifndef options_hc:\Users\goldi\code\arcade-led-control\zones\src\options.cpp
#define options_h
#endif

#include "zone.h"
#include "../../common/leds.h"

const int LEDS[] = {
  OPTIONS_LED_R,
  OPTIONS_LED_G,
  OPTIONS_LED_B
};

const ANIMATION_TYPE ANIMATION_TYPES[] = {    
    STATIC,
    // COLOR_SHIFT,
    FADE,
    // PULSE,
    OFF
};

class Options : public Zone {
  public:
    Options::Options() {
      leds* = LEDS;
      animationTypes = ANIMATION_TYPES;
    }
};