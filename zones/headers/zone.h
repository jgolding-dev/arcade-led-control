#ifndef zone_h
#define zone_h

#include <string>
#include "Arduino.h"
#include "../../common/leds.h"
#include "../../common/brightness_levels.h"
#include <FastLED.h>

// -------- Animation Data Structures -------- //

enum ANIMATION_TYPE {
    STATIC,
    // COLOR_SHIFT,
    FADE,
    // PULSE,
    OFF,
    IDLE
};

const ANIMATION_TYPE FULL_ANIMATION_TYPES[] = {   
    // CUSTOM, 
    STATIC,
    // COLOR_SHIFT,
    FADE,
    // PULSE,
    OFF
};

const ANIMATION_TYPE OPTIONS_ANIMATION_TYPES[] = {    
    STATIC,
    // COLOR_SHIFT,
    FADE,
    // PULSE,
    OFF
};

const ANIMATION_TYPE PLAYER1_ANIMATION_TYPES[] = {    
    STATIC,
    // COLOR_SHIFT,
    FADE,
    // PULSE,
    OFF
};

const ANIMATION_TYPE PLAYER2_ANIMATION_TYPES[] = {    
    STATIC,
    // COLOR_SHIFT,
    FADE,
    // PULSE,
    OFF
};

const ANIMATION_TYPE BACKLIGHT_ANIMATION_TYPES[] = {    
    STATIC,
    // COLOR_SHIFT,
    FADE,
    // PULSE,
    OFF
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

// Parent Class
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
    void idle();
    void wake();
    void startCycleAnimation();
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
    void _setLEDPinBrightness(int ledPin, int percent);
    void _setColor();
};

// -------- Child Classes -------- //

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

class Options : public Zone {
  public:
    // Constructor
    Options(int brightness);
  private:
    const int* _ledPins;
};

class Player1 : public Zone {
  public:
    Player1(int brightness);
  private:
    // Array to hold LED color data
    CRGB _leds[PLAYER1_LED_COUNT];
};

class Player2 : public Zone {
  public:
    Player2(int brightness);
  private:
    // Array to hold LED color data
    CRGB _leds[PLAYER2_LED_COUNT];
};

class Backlight : public Zone {
  public:
    Backlight(int brightness);
  private:
    // Array to hold LED color data
    CRGB* _leds;
};

#endif