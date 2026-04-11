#include <zone.h>

Options::Options(int brightness)
  : Zone(brightness) {}

void Options::setup() {
  animationTypes = OPTIONS_ANIMATION_TYPES;
  previousAnimation = STATIC;
  currentAnimation = IDLE;
  _staticColorIndex = 0;
  _fadeStepIndex = 1;  // FADE_STEP_NORMAL
  _fadeColorIndex = 0;
  FastLED.addLeds<OPTIONS_BUTTONS_LED_TYPE, OPTIONS_BUTTONS_DATA_PIN, COLOR_ORDER>(_leds, OPTIONS_BUTTONS_LED_COUNT);
  FastLED.setBrightness(_currentBrightness);
}

/**
 * Advances to the next frame of the current animation
 */
void Options::process() {
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
void Options::cycleAnimationModifier() {
  switch (currentAnimation) {
    case STATIC:
      _staticColorIndex = (_staticColorIndex + 1) % (sizeof(STATIC_COLORS) / sizeof(STATIC_COLORS[0]));
      Zone::setAllLEDs(STATIC_COLORS[_staticColorIndex]);
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
* Sets the RGB color value of all LEDs in this zone
* @param rValue the brightness value of the red channel
* @param gValue the brightness value of the green channel
* @param bValue the brightness value of the blue channel
*/
void Options::setAllLEDs(uint8_t rValue, uint8_t gValue, uint8_t bValue) {
  Serial.println("Setting Options LEDs");
  delay(50);
  for (int i = 0; i < OPTIONS_BUTTONS_LED_COUNT; i++) {
    _leds[i].r = rValue;
    _leds[i].g = gValue;
    _leds[i].b = bValue;
  }
  FastLED.show();
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
*/
void Options::_setSFTurbo() {
  Serial.println("Setting Options SF_Turbo");
  delay(50);

  // Zone::setAllLEDs(BLACK);
  Zone::setAllLEDs(WHITE);

  FastLED.show();
}