#include "../headers/player1.h"

const std::string NAME = "PLAYER1";

Player1:Player1(int brightness) : Zone(brightness) {}

void Player1::setup() {
  animationTypes = PLAYER1_ANIMATION_TYPES;
  name = NAME;
  currentAnimation = STATIC;
  previousAnimation = IDLE;
  _staticColorIndex = 0;
  FastLED.addLeds<PLAYER1_LED_TYPE, PLAYER1_LED_PIN, COLOR_ORDER>(_leds, PLAYER1_LED_COUNT);
  FastLED.setBrightness(_currentBrightness);
}

/**
 * Advances to the next frame of the current animation
 */
void Player1::process() {
  switch (currentAnimation) {
    case FADE:
      _animateFadeRGB();
      break;
    default:
      // No animation
      break;
  }
}

void Player1:setMasterBrightness(int value) {
  _currentBrightness = value;
  FastLED.setBrightness(_currentBrightness);
}

/**
 * Cycles the currently selected animation to the the next modifier
 */
void Player1::cycleAnimationModifier() {
  switch (currentAnimation) {
    case STATIC:
      _staticColorIndex = (_staticColorIndex + 1) % (sizeof(STATIC_COLOR) / sizeof(STATIC_COLOR[0]));
      _setColor(STATIC_COLOR[_staticColorIndex]);
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
void Player1::setAllLEDs(int rValue, int gValue, int bValue) {
  for (int i = 0; i < (sizeof(_leds) / sizeof(_leds[0]); i++) {
    _leds[i].r = rValue;
    _leds[i].g = gValue;
    _leds[i].b = bValue;
  }
}