#ifndef player2_h
  #define player2_h

  #include "zone.h"
  #include "../../common/leds.h"

  const ANIMATION_TYPE PLAYER2_ANIMATION_TYPES[] = {    
      STATIC,
      // COLOR_SHIFT,
      FADE,
      // PULSE,
      OFF
  };

  class Player2 : public Zone {
    public:
      Player2(int brightness);
    private:
      // Array to hold LED color data
      CRGB _leds[PLAYER2_LED_COUNT];
  };

#endif