#ifndef zone_h
#define zone_h
#endif

#include <string>
#include "Arduino.h"

enum ANIMATION_TYPE {
    STATIC,
    // COLOR_SHIFT,
    FADE,
    // PULSE,
    OFF,
    IDLE
};

const uint32_t STATIC_COLORS[] = {
    0x0000FF, // Blue
    0xFF0000, // Red
    0x00FF00, // Green
    0xFFFFFF, // White
    0xFFFF00, // Yellow
    0xFF00FF, // Magenta
    0x00FFFF  // Cyan
};

class Zone {
  public:
    const std::string name;
    const int* ledPins;
    const ANIMATION_TYPE _animationTypes;
    ANIMATION_TYPE currentAnimation;
    ANIMATION_TYPE previousAnimation;

    void setup();
    void process();
    void reset();
    void setAnimationType();
    void cycleAnimationType();
    void cycleAnimationModifier();
    void setAllLEDs(int r, int g, int b);
    void setBrightness(int ledPin, int percent);
    void startCycleAnimation() {
      _cycleAnimationActive = true;
    }
    void idle() {
      previousAnimation = currentAnimation;
      currentAnimation = IDLE;
      reset();
    }
    void wake() {
      if (currentAnimation == IDLE) {
        currentAnimation = previousAnimation;
        previousAnimation = IDLE;
      }
    }
  private:
    bool _cycleAnimationActive;
    int _staticColorIndex;
    void _setColor();
};