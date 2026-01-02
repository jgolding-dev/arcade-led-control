#include "../headers/options.h"

const std::string NAME = "OPTIONS";

Options::Options(int brightness): Zone(brightness) {}

void Options::setup() {
  animationTypes = OPTIONS_ANIMATION_TYPES;
  name = NAME;
  currentAnimation = STATIC;
  previousAnimation = IDLE;
  _staticColorIndex = 0;
  _ledPins = OPTIONS_LEDS;
  reset();
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
* Updates the currently selected animation, and tracks the previous set animation.
* @param animType The animation type to set.
*/
void Options::setAnimationType(int animType) {
    previousAnimationType = currentAnimationType;
    currentAnimationType = animType;
    reset();
    switch (animType) {
        case STATIC:
            _setColor(STATIC_COLORS[_staticColorIndex]);
            break;
        default:
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
void Zone::setAllLEDs(int rValue, int gValue, int bValue) {
  _setLEDPinBrightness(OPTIONS_PIN_R, rValue);
  _setLEDPinBrightness(OPTIONS_PIN_G, gValue);
  _setLEDPinBrightness(OPTIONS_PIN_B, bValue);
}