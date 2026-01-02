#ifndef player1_h
  #define player1_h

  #include "zone.h"
  #include "../../common/leds.h"

  const ANIMATION_TYPE PLAYER1_ANIMATION_TYPES[] = {    
      STATIC,
      // COLOR_SHIFT,
      FADE,
      // PULSE,
      OFF
  };

  class Player1 : public Zone {
    public:
      Player1(int brightness);
    private:
      // Array to hold LED color data
      CRGB _leds[PLAYER1_LED_COUNT];
  };

#endif