#ifndef options_h
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

const unsigned long FADE_STEP_MS = 25;

class Options : public Zone {
  public:
    Options::Options() {
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