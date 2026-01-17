#include <zone.h>

Accent::Accent(int brightness)
  : Zone(brightness) {}

void Accent::setup() {
  animationTypes = ACCENT_ANIMATION_TYPES;
  previousAnimation = STATIC;
  currentAnimation = IDLE;
  _staticColorIndex = 0;
  _fadeStepIndex = 1;  // FADE_STEP_NORMAL
  _fadeColorIndex = 0;
  FastLED.addLeds<ACCENT_LED_TYPE, ACCENT_DATA_PIN, COLOR_ORDER>(_leds, ACCENT_LED_COUNT);
  FastLED.setBrightness(_currentBrightness);
}

/**
 * Advances to the next frame of the current animation
 */
void Accent::process() {
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
void Accent::cycleAnimationModifier() {
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
void Accent::setAllLEDs(int rValue, int gValue, int bValue) {
  Serial.println("Setting Accent LEDs");
  for (int i = 0; i < ACCENT_LED_COUNT; i++) {
    _leds[i].r = rValue;
    _leds[i].g = gValue;
    _leds[i].b = bValue;
  }
  FastLED.show();
}