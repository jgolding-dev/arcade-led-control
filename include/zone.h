#ifndef zone_h
#define zone_h

#include <Arduino.h>
#include <pins.h>
#include <led_layout.h>
#include <input_protocol.h>
#include <brightness_levels.h>
#include <fastled_config.h>
#include <FastLED.h>
#include <string.h>

// -------- Animation Data Structures -------- //

enum ANIMATION_TYPE {
  CUSTOM,
  STATIC,
  COLOR_SHIFT,
  RAINBOW,
  FADE,
  // PULSE,
  OFF,
  IDLE
};

const ANIMATION_TYPE ANIMATION_TYPES[] = {
  CUSTOM,
  STATIC,
  COLOR_SHIFT,
  RAINBOW,
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

// These values are accumulators for the color shift animation. Higher values will result in faster color shifts.
const fl::accum88 COLOR_SHIFT_SPEED_FAST = 10.0;
const fl::accum88 COLOR_SHIFT_SPEED_NORMAL = 20.0;
const fl::accum88 COLOR_SHIFT_SPEED_SLOW = 30.0;

const fl::accum88 COLOR_SHIFT_SPEEDS[] = {
  COLOR_SHIFT_SPEED_FAST,
  COLOR_SHIFT_SPEED_NORMAL,
  COLOR_SHIFT_SPEED_SLOW
};

const unsigned long ZONE_SWITCH_ANIMATION_STEP_MS = 350;

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
  void startZoneSwitchAnimation();
  bool isZoneSwitchActive();
  void cycleAnimationType();
  void setAnimationType(ANIMATION_TYPE animType);
  void cycleAnimationModifier();
  void setAnimationModifier(int modifierIndex);
  void setAllZone(const RGB_t &color);
  void setLEDs(CRGB* leds, const RGB_t &color, int count);
  void setLEDs(CRGB* leds, const RGB_t &color, uint8_t* indexes, int size);
  void setMasterBrightness(int value);
  void process();

  // Virtual functions to be overridden by children
  virtual void idle();
  virtual void wake();
  virtual void setup();
  virtual void setAllZone(uint8_t rValue, uint8_t gValue, uint8_t bValue);
  virtual void applyCustom(const CustomType &type);
  virtual void endZoneSwitchAnimation();
  virtual void fillRainbow(uint8_t gHueValue) {};
  virtual void fillSolid(uint8_t hue) {};
  
protected:
  bool _switchAnimationActive;
  int _staticColorIndex;
  int _customTypeIndex;
  int _currentBrightness;
  int _lastFadeAnimStepMs;
  int _fadeStepIndex;
  int _fadeColorIndex;
  int _fadePercent;
  int _fadeDir;
  int _zoneSwitchBlinkDir;
  int _colorShiftSpeedIndex;
  int _rainbowShiftSpeedIndex;
  uint8_t _gHue; // tracks starting hue for certain animations
  unsigned long _lastZoneSwitchAnimStepMs;

  // blend animation data
  CRGBPalette16 colorPalette;
  TBlendType _blendType;
  uint8_t _blendIndex;    // Tracks the current position in the blend color palette

  // Virtual functions to be overridden by children
  virtual void _animateCustom(){};
  virtual void _setSFTurbo(){};
  
  void _animateFadeRGB();
  void _animateRainbow();
  void _animateColorShift();
  void _setLED(CRGB* leds, const RGB_t &color, int index);
  void _processZoneSwitchAnimation();
};

// -------- Child Classes -------- //

class Options : public Zone {
  public:
    // Constructor
    Options(int brightness);

    // Override Functions
    void idle();
    void wake();
    void setup();
    void setAllZone(uint8_t rValue, uint8_t gValue, uint8_t bValue);
    void fillRainbow(uint8_t gHueValue);
    void fillSolid(uint8_t hue);
  private:
    // Array to hold LED color data
    CRGB _leds[OPTIONS_BUTTONS_LED_COUNT];

    // override functions
    void _setSFTurbo();
};

class Player1 : public Zone {
public:
  // Constructor
  Player1(int brightness);

  // Override Functions
  void setup();
  void setAllZone(uint8_t rValue, uint8_t gValue, uint8_t bValue);
  void fillRainbow(uint8_t gHueValue);
  void fillSolid(uint8_t hue);
private:
  // Array to hold LED color data
  CRGB _buttonLeds[ACTION_BUTTONS_LED_COUNT];
  CRGB _joystickLeds[JOYSTICK_RING_LED_COUNT];
  CRGB _balltopLeds[JOYSTICK_BALLTOP_LED_COUNT];

  // override functions
  void _setSFTurbo();
};

class Player2 : public Zone {
public:
  // Constructor
  Player2(int brightness);

  // Override Functions
  void setup();
  void setAllZone(uint8_t rValue, uint8_t gValue, uint8_t bValue);
  void fillRainbow(uint8_t gHueValue);
  void fillSolid(uint8_t hue);
private:
  // Array to hold LED color data
  CRGB _buttonLeds[ACTION_BUTTONS_LED_COUNT];
  CRGB _joystickLeds[JOYSTICK_RING_LED_COUNT];
  CRGB _balltopLeds[JOYSTICK_BALLTOP_LED_COUNT];

  // override functions
  void _setSFTurbo();
};

class Accent : public Zone {
public:
  // Constructor
  Accent(int brightness);

  // Override Functions
  void setup();
  void setAllZone(uint8_t rValue, uint8_t gValue, uint8_t bValue);
  void fillRainbow(uint8_t gHueValue);
  void fillSolid(uint8_t hue);
private:
  // Array to hold LED color data
  CRGB _leds[ACCENT_LED_COUNT];

  // override functions
  // void _setSFTurbo();
};

class Full : public Zone {
public:
  // Constructor
  Full(int brightness, Player1* p1Zone, Player2* p2Zone, Options* opZone, Accent* accZone);

  // Override Functions
  void setup();
  void setAllZone(uint8_t rValue, uint8_t gValue, uint8_t bValue);
  void applyCustom(const CustomType &type);
  void fillRainbow(uint8_t gHueValue);
  void fillSolid(uint8_t hue);
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
    void setAllZone(uint8_t rValue, uint8_t gValue, uint8_t bValue);
    void fillRainbow(uint8_t gHueValue);
    void fillSolid(uint8_t hue);
  private:
    // sub-zones
    Player1* _player1Zone;
    Player2* _player2Zone;
    Options* _optionsZone;
};

#endif