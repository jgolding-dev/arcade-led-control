#include <zone.h>

// const std::string NAME = "FULL";

Full::Full(int brightness)
  : Zone(brightness) {}

void Full::setup() {
  animationTypes = FULL_ANIMATION_TYPES;
  // name = NAME;
  currentAnimation = IDLE;
  // previousAnimation = IDLE;
  _staticColorIndex = 0;
  _fadeStepIndex = 1;  // FADE_STEP_NORMAL
  _fadeColorIndex = 0;
  _optionsLedPins = OPTIONS_LEDS;
  FastLED.addLeds<PLAYER1_LED_TYPE, PLAYER1_DATA_PIN, COLOR_ORDER>(_player1Leds, PLAYER1_LED_COUNT);
  FastLED.addLeds<PLAYER2_LED_TYPE, PLAYER2_DATA_PIN, COLOR_ORDER>(_player2Leds, PLAYER2_LED_COUNT);
  FastLED.addLeds<BACKLIGHT_LED_TYPE, BACKLIGHT_DATA_PIN, COLOR_ORDER>(_backlightLeds, BACKLIGHT_LED_COUNT);
  FastLED.setBrightness(_currentBrightness);
  setAnimationType(STATIC);
}

/**
 * Advances to the next frame of the current animation
 */
void Full::process() {
  switch (currentAnimation) {
    case FADE:
      _animateFadeRGB();
      break;
    default:
      // No animation
      break;
  }
}

/**
 * Cycles the currently selected animation to the the next modifier
 */
void Full::cycleAnimationModifier() {
  switch (currentAnimation) {
    case STATIC:
      _staticColorIndex = (_staticColorIndex + 1) % (sizeof(STATIC_COLORS) / sizeof(STATIC_COLORS[0]));
      _setColor(STATIC_COLORS[_staticColorIndex]);
      break;
    case FADE:
      _fadeStepIndex = (_fadeStepIndex + 1) % (sizeof(FADE_STEP_MS) / sizeof(FADE_STEP_MS[0]));
      _lastAnimStepMs = 0;
      break;
    default:
      // No modifier
      break;
  }
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param rValue the brightness value of the red channel
* @param gValue the brightness value of the green channel
* @param bValue the brightness value of the blue channel
*/
void Full::setAllLEDs(int rValue, int gValue, int bValue) {
  _setLEDPinBrightness(OPTIONS_PIN_R, rValue);
  _setLEDPinBrightness(OPTIONS_PIN_G, gValue);
  _setLEDPinBrightness(OPTIONS_PIN_B, bValue);

  for (int i = 0; i < PLAYER1_LED_COUNT; i++) {
    _player1Leds[i].r = rValue;
    _player1Leds[i].g = gValue;
    _player1Leds[i].b = bValue;
  }
  for (int i = 0; i < PLAYER2_LED_COUNT; i++) {
    _player2Leds[i].r = rValue;
    _player2Leds[i].g = gValue;
    _player2Leds[i].b = bValue;
  }
  for (int i = 0; i < BACKLIGHT_LED_COUNT; i++) {
    _backlightLeds[i].r = rValue;
    _backlightLeds[i].g = gValue;
    _backlightLeds[i].b = bValue;
  }
  FastLED.show();
}