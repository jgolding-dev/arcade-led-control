#include "../headers/options.h"
#include ""

const std::string NAME = "OPTIONS";

void Options::setup() {
  name = NAME;
  currentAnimation = STATIC;
  previousAnimation = IDLE;
  _staticColorIndex = 0;
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

void cycleAnimationType() {

}

/**
 * Cycles the currently selected animation to the the next modifier
 */
void Options::cycleAnimationModifier() {
  switch (currentAnimation) {
    case STATIC:
      _staticColorIndex = (_staticColorIndex + 1) % (sizeof(STATIC_COLOR_LIST) / sizeof(STATIC_COLOR_LIST[0]));
      _setColor(STATIC_COLOR_LIST[_staticColorIndex]);
        break;
    default:
      // No modifier
      break;
  }
}

/**
* Fades each color (R/G/B) in and out, sequentially
*/
void Options::_animateFadeRGB() {
    unsigned long now = millis();
    if (now - _lastAnimStepMs < _fadeStepMs) {
        return;
    }
    _lastAnimStepMs = now;
    // Turn off all LEDs first
    setAllLEDs(0, 0, 0);

    int pin = _ledPins[_fadeColorIndex];

    // Calculate brightness as a percentage of the current brightness setting
    float normalized = _fadePercent / 100.0;
    int brightness = normalized * ANIMATION_BRIGHTNESS_LIST[_currentBrightness];
    _setBrightness(pin, brightness);

    _fadePercent += _fadeDir;

    if (_fadePercent >= 100) {
        _fadeDir = -1;
    }
    else if (_fadePercent <= 0) {
        _fadeDir = 1;
        _fadeColorIndex = (_fadeColorIndex + 1) % (sizeof(_ledPins) / sizeof(_ledPins)[0]);
    }
}