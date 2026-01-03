#include "zone.h"

// const std::string NAME = "OPTIONS";

Options::Options(int brightness): Zone(brightness) {}

void Options::setup() {
  animationTypes = OPTIONS_ANIMATION_TYPES;
  // // name = NAME;
  currentAnimation = IDLE;
  _staticColorIndex = 0;
  _ledPins = OPTIONS_LEDS;
  _fadeColorIndex = 0;
  setAnimationType(STATIC);
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

// /**
// * Updates the currently selected animation, and tracks the previous set animation.
// * @param animType The animation type to set.
// */
// void Options::setAnimationType(int animType) {
//     previousAnimationType = currentAnimationType;
//     currentAnimationType = animType;
//     reset();
//     switch (animType) {
//         case STATIC:
//             _setColor(STATIC_COLORS[_staticColorIndex]);
//             break;
//         default:
//             break;
//     }
// }

/**
 * Cycles the currently selected animation to the the next modifier
 */
void Options::cycleAnimationModifier() {
  switch (currentAnimation) {
    case STATIC:
      _staticColorIndex = (_staticColorIndex + 1) % (sizeof(STATIC_COLORS) / sizeof(STATIC_COLORS[0]));
      _setColor(STATIC_COLORS[_staticColorIndex]);
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
    if (now - _lastAnimStepMs < _fadeStepMs) {
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
        _fadeColorIndex = (_fadeColorIndex + 1) % (sizeof(_ledPins) / sizeof(_ledPins)[0]);
    }
}