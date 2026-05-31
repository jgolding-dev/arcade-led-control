#include <zone.h>

Options::Options(int brightness)
  : Zone(brightness) {}

void Options::setup() {
  animationTypes = OPTIONS_ANIMATION_TYPES;
  previousAnimation = CUSTOM;
  currentAnimation = IDLE;
  _staticColorIndex = 0;
  _fadeStepIndex = 1;  // FADE_STEP_NORMAL
  _fadeColorIndex = 0;
  FastLED.addLeds<OPTIONS_BUTTONS_LED_TYPE, OPTIONS_BUTTONS_DATA_PIN, GRB>(_leds, OPTIONS_BUTTONS_LED_COUNT);
  FastLED.setBrightness(_currentBrightness);

  // Overlay buttons default to set colors
  _setLED(_leds, RGB_GREEN, HOME_LED);
  _setLED(_leds, RGB_BLUE, EXTRA1_LED);
}

/**
* Puts the zone in an idle state
*/
void Options::idle() {
  if (currentAnimation != IDLE) {
    _setLED(_leds, RGB_BLACK, HOME_LED);
    _setLED(_leds, RGB_BLACK, EXTRA1_LED);
    setAnimationType(IDLE);
  }
}

/**
* Puts the zone in a wake state
*/
void Options::wake() {
  if (currentAnimation == IDLE) {
    _setLED(_leds, RGB_GREEN, HOME_LED);
    _setLED(_leds, RGB_BLUE, EXTRA1_LED);
    setAnimationType(previousAnimation);
  }
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
      _staticColorIndex = (_staticColorIndex + 1) % (sizeof(COLORS) / sizeof(COLORS[0]));
      Zone::setAllZone(COLORS[_staticColorIndex]);
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
void Options::setAllZone(uint8_t rValue, uint8_t gValue, uint8_t bValue) {
  Serial.println("Setting Options LEDs");
  for (int i = 2; i < OPTIONS_BUTTONS_LED_COUNT; i++) { // Exclude HOME buttons
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

  Zone::setAllZone(RGB_WHITE);

  FastLED.show();
}