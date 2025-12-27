#ifndef zone_h
#define zone_h
#endif

#include <string>
#include "Arduino.h"

class Zone {
  public:
    const std::string name;
    const int* leds;
    const ANIMATION_TYPE _animationTypes;
    ANIMATION_TYPE currentAnimation;
    ANIMATION_TYPE previousAnimation;

    void setup();
    void process();
    void cycleAnimationType();
    void cycleAnimationModifier();
    void idle() {
      previousAnimation = currentAnimation;
      currentAnimation = IDLE;
      _reset();
    }
    void wake() {
      if (currentAnimation == IDLE) {
        currentAnimation = previousAnimation;
        previousAnimation = IDLE;
      }
    }
  }
  private:
    bool _cycleAnimationActive;
    int _staticColorIndex;
    _reset();
}