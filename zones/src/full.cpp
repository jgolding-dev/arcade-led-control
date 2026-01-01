#include "../headers/options.h"
#include "../../common/leds.h"

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

void Zone::cycleAnimationType() {
    ANIMATION_TYPE nextType = ANIMATION_TYPES[(_currentAnimation + 1) % (sizeof(ANIMATION_TYPES) / sizeof(ANIMATION_TYPES)[0])];
    updateAnimationType(nextType);
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
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param rValue the brightness value of the red channel
* @param gValue the brightness value of the green channel
* @param bValue the brightness value of the blue channel
*/
void Options::setAllLEDs(int rValue, int gValue, int bValue) {
  _setBrightness(OPTIONS_LED_R, rValue);
  _setBrightness(OPTIONS_LED_G, gValue);
  _setBrightness(OPTIONS_LED_B, bValue);
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

    int pin = ledPins[_fadeColorIndex];

    // Calculate brightness as a percentage of the current brightness setting
    // float normalized = _fadePercent / 100.0;
    // int brightness = normalized * ANIMATION_BRIGHTNESS_LIST[_currentBrightness];
    // _setBrightness(pin, brightness);
    _setBrightness(pin, _fadePercent);

    _fadePercent += _fadeDir;

    if (_fadePercent >= 100) {
        _fadeDir = -1;
    }
    else if (_fadePercent <= 0) {
        _fadeDir = 1;
        _fadeColorIndex = (_fadeColorIndex + 1) % (sizeof(ledPins) / sizeof(ledPins)[0]);
    }
}

/**
* Sets the brightness value of single LED pin to the specified percentage value
* @param ledPin The pin number of the LED to set the brightness of
* @param percent The brightness percentage value (0-100)
*/
void Options::_setBrightness(int ledPin, int percent) {
    // Constrain percentage to 0-100
    percent = constrain(percent, 0, 100);

    // set brightness level using gamma correction
    float gamma = 2.2;
    float normalized = percent / 100.0;
    int brightness = pow(normalized, gamma) * 255;
    analogWrite(ledPin, brightness);
}