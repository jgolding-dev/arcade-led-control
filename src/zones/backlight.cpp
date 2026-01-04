#include "zone.h"

// const std::string NAME = "BACKLIGHT";

Backlight::Backlight(int brightness)
  : Zone(brightness) {}

void Backlight::setup() {
  animationTypes = BACKLIGHT_ANIMATION_TYPES;
  // name = NAME;
  currentAnimation = IDLE;
  _staticColorIndex = 0;
  _fadeStepIndex = 1;  // FADE_STEP_NORMAL
  _fadeColorIndex = 0;
  FastLED.addLeds<BACKLIGHT_LED_TYPE, BACKLIGHT_DATA_PIN, COLOR_ORDER>(_leds, BACKLIGHT_LED_COUNT);
  FastLED.setBrightness(_currentBrightness);
  setAnimationType(STATIC);
}

/**
 * Advances to the next frame of the current animation
 */
void Backlight::process() {
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
void Backlight::cycleAnimationModifier() {
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
void Backlight::setAllLEDs(int rValue, int gValue, int bValue) {
  Serial.println("Setting BACKLIGHT LEDs");
  for (int i = 0; i < BACKLIGHT_LED_COUNT; i++) {
    _leds[i].r = rValue;
    _leds[i].g = gValue;
    _leds[i].b = bValue;
  }
  FastLED.show();
}