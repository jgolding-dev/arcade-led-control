#ifndef options_h
  #define options_h

  #include "zone.h"
  #include "../../common/leds.h"

  const ANIMATION_TYPE OPTIONS_ANIMATION_TYPES[] = {    
      STATIC,
      // COLOR_SHIFT,
      FADE,
      // PULSE,
      OFF
  };

  const unsigned long FADE_STEP_MS = 25;

  class Options : public Zone {
    public:
      // Constructor
      Options(int brightness);
    private:
      const int* _ledPins;
  };

#endif