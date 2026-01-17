#include <zone.h>

Options::Options(int brightness): Zone(brightness) {}

void Options::setup() {
  animationTypes = OPTIONS_ANIMATION_TYPES;
  previousAnimation = STATIC;
  currentAnimation = IDLE;
  _ledPins = OPTIONS_LED_PINS;
  _fadeStepIndex = 1; // FADE_STEP_NORMAL
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

void Options::setMasterBrightness(int value) {
  _currentBrightness = value;
}

/**
 * Cycles the current animation to the the next modifier
 */
void Options::cycleAnimationModifier() {
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
void Options::setAllLEDs(int rValue, int gValue, int bValue) {
  _setLEDPinBrightness(OPTIONS_PIN_R, rValue);
  _setLEDPinBrightness(OPTIONS_PIN_G, gValue);
  _setLEDPinBrightness(OPTIONS_PIN_B, bValue);
}

/**
* Fades each color (R/G/B) in and out, sequentially
*/
void Options::_animateFadeRGB() {
    unsigned long now = millis();
    if (now - _lastAnimStepMs < FADE_STEP_MS[_fadeStepIndex]) {
        return;
    }
    _lastAnimStepMs = now;
    // Turn off all LEDs first
    setAllLEDs(0, 0, 0);

    int pin = _ledPins[_fadeColorIndex];

    // Calculate brightness as a percentage of the current brightness setting
    // float normalized = _fadePercent / 100.0;
    // int brightness = normalized * ANIMATION_BRIGHTNESS_LIST[_currentBrightness];
    // _setLEDPinBrightness(pin, brightness);
    _setLEDPinBrightness(pin, _fadePercent);

    _fadePercent += _fadeDir;

    if (_fadePercent >= 100) {
        _fadeDir = -1;
    }
    else if (_fadePercent <= 0) {
        _fadeDir = 1;
        _fadeColorIndex = (_fadeColorIndex + 1) % OPTIONS_LED_COUNT;
    }
}