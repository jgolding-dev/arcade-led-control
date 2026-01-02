#ifndef zone_h
#define zone_h

#include <string>
#include "Arduino.h"
#include "../../common/leds.h"
#include "../../common/brightness_levels.h"

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
    // Constructor
    Zone(int brightness);

    const std::string name;
    const ANIMATION_TYPE* animationTypes;
    ANIMATION_TYPE currentAnimation;
    ANIMATION_TYPE previousAnimation;

    void setup();
    void process();
    void reset();
    void setAnimationType();
    void cycleAnimationType();
    void cycleAnimationModifier();
    void setAllLEDs(int r, int g, int b);
    void setMasterBrightness(int value);
  private:
    bool _cycleAnimationActive;
    int _staticColorIndex;
    int _currentBrightness;
    int _lastAnimStepMs;
    int _fadeStepMs;
    int _fadeColorIndex;
    int _fadePercent;
    int _fadeDir;
    void setLEDPinBrightness(int ledPin, int percent);
    void _setColor();
};

#endif