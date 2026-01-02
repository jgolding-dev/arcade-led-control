#ifndef backlight_h
  #define backlight_h

  #include "zone.h"
  #include "../../common/leds.h"

  const ANIMATION_TYPE BACKLIGHT_ANIMATION_TYPES[] = {    
      STATIC,
      // COLOR_SHIFT,
      FADE,
      // PULSE,
      OFF
  };

  class Backlight : public Zone {
    public:
      Backlight(int brightness);
    private:
      // Array to hold LED color data
      CRGB* _leds;
  };

#endif