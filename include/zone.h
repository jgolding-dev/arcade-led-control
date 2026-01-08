#ifndef zone_h
#define zone_h

#include <Arduino.h>
#include <leds.h>
#include <brightness_levels.h>
#define FASTLED_RP2040_CLOCKLESS_M0_FALLBACK 0
#define FASTLED_RP2040_CLOCKLESS_PIO 1
#include <FastLED.h>

// -------- Animation Data Structures -------- //

enum ANIMATION_TYPE {
  // PRESET,
  STATIC,
  // COLOR_SHIFT,
  FADE,
  // PULSE,
  OFF,
  IDLE
};

const ANIMATION_TYPE FULL_ANIMATION_TYPES[] = {
  // PRESET,
  STATIC,
  // COLOR_SHIFT,
  FADE,
  // PULSE,
  // OFF
};

const ANIMATION_TYPE OPTIONS_ANIMATION_TYPES[] = {
  STATIC,
  // COLOR_SHIFT,
  FADE,
  // PULSE,
  // OFF
};

const ANIMATION_TYPE PLAYER1_ANIMATION_TYPES[] = {
  STATIC,
  // COLOR_SHIFT,
  FADE,
  // PULSE,
  // OFF
};

const ANIMATION_TYPE PLAYER2_ANIMATION_TYPES[] = {
  STATIC,
  // COLOR_SHIFT,
  FADE,
  // PULSE,
  // OFF
};

const ANIMATION_TYPE BACKLIGHT_ANIMATION_TYPES[] = {
  STATIC,
  // COLOR_SHIFT,
  FADE,
  // PULSE,
  // OFF
};

const uint32_t STATIC_COLORS[] = {
  0x0000FF,  // Blue
  0xFF0000,  // Red
  0x00FF00,  // Green
  0xFFFFFF,  // White
  0xFFFF00,  // Yellow
  0xFF00FF,  // Magenta
  0x00FFFF   // Cyan
};

const unsigned long FADE_STEP_FAST = 15;
const unsigned long FADE_STEP_NORMAL = 25;
const unsigned long FADE_STEP_SLOW = 40;

const unsigned long FADE_STEP_MS[] = {
  FADE_STEP_FAST,
  FADE_STEP_NORMAL,
  FADE_STEP_SLOW
};

// Parent Class
class Zone {
public:
  // Constructor
  Zone(int brightness);

  // Virtual Destructor
  virtual ~Zone() = default;

  const ANIMATION_TYPE* animationTypes;
  ANIMATION_TYPE currentAnimation;
  ANIMATION_TYPE previousAnimation;

  void idle();
  void wake();
  void startCycleAnimation();
  void setAnimationType(ANIMATION_TYPE animType);
  void cycleAnimationType();

  // Virtual functions to be overridden by children
  virtual void reset();
  virtual void setup();
  virtual void process();
  virtual void cycleAnimationModifier();
  virtual void setMasterBrightness(int value);
  virtual void setAllLEDs(int r, int g, int b);
protected:
  bool _cycleAnimationActive;
  int _staticColorIndex;
  int _currentBrightness;
  int _lastAnimStepMs;
  int _fadeStepIndex;
  int _fadeColorIndex;
  int _fadePercent;
  int _fadeDir;
  virtual void _animateFadeRGB();
  void _setLEDPinBrightness(int ledPin, int percent);
  void _setColor(uint32_t color);
};

// -------- Child Classes -------- //

class Full : public Zone {
public:
  // Constructor
  Full(int brightness);

  // Override Functions
  void setup();
  void process();
  void cycleAnimationModifier();
  void setAllLEDs(int r, int g, int b);
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

  // Override Functions
  void setup();
  void process();
  void cycleAnimationModifier();
  void setMasterBrightness(int value);
  void setAllLEDs(int r, int g, int b);
private:
  const int* _ledPins;
  void _animateFadeRGB();
};

class Player1 : public Zone {
public:
  // Constructor
  Player1(int brightness);

  // Override Functions
  void setup();
  void process();
  void cycleAnimationModifier();
  void setAllLEDs(int r, int g, int b);
private:
  // Array to hold LED color data
  CRGB _leds[PLAYER1_LED_COUNT];
};

class Player2 : public Zone {
public:
  // Constructor
  Player2(int brightness);

  // Override Functions
  void setup();
  void process();
  void cycleAnimationModifier();
  void setAllLEDs(int r, int g, int b);
private:
  // Array to hold LED color data
  CRGB _leds[PLAYER2_LED_COUNT];
};

class Backlight : public Zone {
public:
  // Constructor
  Backlight(int brightness);

  // Override Functions
  void setup();
  void process();
  void cycleAnimationModifier();
  void setAllLEDs(int r, int g, int b);
private:
  // Array to hold LED color data
  CRGB _leds[BACKLIGHT_LED_COUNT];
};

#endif