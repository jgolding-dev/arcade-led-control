#ifndef zone_h
#define zone_h

#include <Arduino.h>
#include <pins.h>
#include <led_layout.h>
#include <input_protocol.h>
#include <brightness_levels.h>
#include <fastled_config.h>
#include <FastLED.h>

// -------- Animation Data Structures -------- //

enum ANIMATION_TYPE {
  CUSTOM,
  STATIC,
  // COLOR_SHIFT,
  FADE,
  // PULSE,
  OFF,
  IDLE
};

const ANIMATION_TYPE FULL_ANIMATION_TYPES[] = {
  CUSTOM,
  STATIC,
  // COLOR_SHIFT,
  FADE,
  // PULSE,
  // OFF
};

const ANIMATION_TYPE OPTIONS_ANIMATION_TYPES[] = {
  CUSTOM,
  STATIC,
  // COLOR_SHIFT,
  FADE,
  // PULSE,
  // OFF
};

const ANIMATION_TYPE PLAYER1_ANIMATION_TYPES[] = {
  CUSTOM,
  STATIC,
  // COLOR_SHIFT,
  FADE,
  // PULSE,
  // OFF
};

const ANIMATION_TYPE PLAYER2_ANIMATION_TYPES[] = {
  CUSTOM,
  STATIC,
  // COLOR_SHIFT,
  FADE,
  // PULSE,
  // OFF
};

const ANIMATION_TYPE ACCENT_ANIMATION_TYPES[] = {
  CUSTOM,
  STATIC,
  // COLOR_SHIFT,
  FADE,
  // PULSE,
  // OFF
};

enum CustomType : uint8_t {
  SF_TURBO = 0
};

const CustomType CUSTOM_TYPES[] = {
  SF_TURBO
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

  void reset();
  void idle();
  void wake();
  void startZoneSwitchAnimation();
  void cycleAnimationType();
  void setAnimationModifier(int modifierIndex);
  void setAllLEDs(const RGB_t &color);
  void setMasterBrightness(int value);


  // Virtual functions to be overridden by children
  virtual void setup();
  virtual void process();
  virtual void setAnimationType(ANIMATION_TYPE animType);
  virtual void cycleAnimationModifier();
  virtual void setAllLEDs(uint8_t r, uint8_t g, uint8_t b);
protected:
  bool _switchAnimationActive;
  int _staticColorIndex;
  int _customTypeIndex;
  int _currentBrightness;
  int _lastAnimStepMs;
  int _fadeStepIndex;
  int _fadeColorIndex;
  int _fadePercent;
  int _fadeDir;
  virtual void _animateCustom();
  virtual void _setCustom(const CustomType &type);
  virtual void _setSFTurbo();
  void _animateFadeRGB();
  void _setLEDPinBrightness(int ledPin, int percent);
  void _setColor(CRGB* leds, const RGB_t &color, int index);
  void _setColor(CRGB* leds, const RGB_t &color, int* indexes, int size);
  void _setAllCRGB(CRGB* leds, const RGB_t &color, int count);
};

// -------- Child Classes -------- //

class Options : public Zone {
  public:
    // Constructor
    Options(int brightness);

    // Override Functions
    void setup();
    void process();
    void cycleAnimationModifier();
    void setAllLEDs(uint8_t r, uint8_t g, uint8_t b);
  private:
    CRGB _leds[OPTIONS_BUTTONS_LED_COUNT];
    void _setSFTurbo();
};

class Player1 : public Zone {
public:
  // Constructor
  Player1(int brightness);

  // Override Functions
  void setup();
  void process();
  void cycleAnimationModifier();
  void setAllLEDs(uint8_t r, uint8_t g, uint8_t b);
private:
  // Array to hold LED color data

  CRGB _buttonLeds[PLAYER1_BUTTONS_LED_COUNT];
  CRGB _joystickLeds[PLAYER1_JOYSTICK_LED_COUNT];
  void _setSFTurbo();
};

class Player2 : public Zone {
public:
  // Constructor
  Player2(int brightness);

  // Override Functions
  void setup();
  void process();
  void cycleAnimationModifier();
  void setAllLEDs(uint8_t r, uint8_t g, uint8_t b);
private:
  // Array to hold LED color data
  CRGB _buttonLeds[PLAYER2_BUTTONS_LED_COUNT];
  CRGB _joystickLeds[PLAYER2_JOYSTICK_LED_COUNT];
  void _setSFTurbo();
};

class Accent : public Zone {
public:
  // Constructor
  Accent(int brightness);

  // Override Functions
  void setup();
  void process();
  void cycleAnimationModifier();
  void setAllLEDs(uint8_t r, uint8_t g, uint8_t b);
private:
  // Array to hold LED color data
  CRGB _leds[ACCENT_LED_COUNT];
};

class Full : public Zone {
public:
  // Constructor
  Full(int brightness, Player1* p1Zone, Player2* p2Zone, Options* opZone, Accent* accZone);

  // Override Functions
  void setup();
  void process();
  void cycleAnimationModifier();
  void setAnimationType(ANIMATION_TYPE animType);
  void setAllLEDs(uint8_t r, uint8_t g, uint8_t b);
private:
  // sub-zones
  Player1* _player1Zone;
  Player2* _player2Zone;
  Options* _optionsZone;
  Accent* _accentZone;

  // Pointer table for iteration
  static constexpr uint8_t ZONE_COUNT = 4;
  Zone* _subZones[ZONE_COUNT];
};

class ControlPanel : public Zone {
  public:
    // Constructor
    ControlPanel(int brightness);

    // Override Functions
    void setup(Player1* p1Zone, Player2* p2Zone, Options* opZone);
    void process();
    void cycleAnimationModifier();
    void setAllLEDs(uint8_t r, uint8_t g, uint8_t b);
  private:
    // sub-zones
    Player1* _player1Zone;
    Player2* _player2Zone;
    Options* _optionsZone;
};

#endif