#ifndef full_h
  #define full_h

  #include "zone.h"
  #include "../../common/leds.h"
  #include <FastLED.h>

  const ANIMATION_TYPE FULL_ANIMATION_TYPES[] = {   
      // CUSTOM, 
      STATIC,
      // COLOR_SHIFT,
      FADE,
      // PULSE,
      OFF
  };

  class Full : public Zone {
    public:
      // Constructor
      Full(int brightness);
    private:
      const int* _optionsLedPins;

      // Arrays to hold LED color data
      CRGB _player1Leds[PLAYER1_LED_COUNT];
      CRGB _player2Leds[PLAYER2_LED_COUNT];
      CRGB _backlightLeds[BACKLIGHT_LED_COUNT];
  };

#endif