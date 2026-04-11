#include <zone.h>

Zone::Zone(int brightness)
  : _currentBrightness(brightness) {}

void Zone::setup() {
  previousAnimation = STATIC;
  currentAnimation = IDLE;
  _fadeStepIndex = 1;  // FADE_STEP_NORMAL
}

/**
 * Advances to the next frame of the current animation
 */
void Zone::process() {
  switch (currentAnimation) {
    case FADE:
      _animateFadeRGB();
      break;
    case CUSTOM:
      _animateCustom();
    default:
      // No animation
      break;
  }
}

void Zone::setMasterBrightness(int value) {
  _currentBrightness = value;
  FastLED.setBrightness(_currentBrightness);
}

/**
* Set the zone switch animation to run at the next frame
*/
void Zone::startZoneSwitchAnimation() {
  _switchAnimationActive = true;
}

/**
* Puts the zone in an idle state
*/
void Zone::idle() {
  if (currentAnimation != IDLE) {
    setAnimationType(IDLE);
  }
}

/**
* Puts the zone in a wake state
*/
void Zone::wake() {
  if (currentAnimation == IDLE) {
    setAnimationType(previousAnimation);
  }
}

/**
* Updates the currently selected animation, and tracks the previous set animation.
* @param animType The animation type to set.
*/
void Zone::setAnimationType(ANIMATION_TYPE animType) {
  previousAnimation = currentAnimation;
  currentAnimation = animType;
  reset();
  setAllLEDs(BLACK);
  switch (animType) {
    case STATIC:
      setAllLEDs(STATIC_COLORS[_staticColorIndex]);
      break;
    case CUSTOM:
      _setCustom(CUSTOM_TYPES[_customTypeIndex]);
    default:
      break;
  }
}

/**
* Sets the modifier value of the currently elected animation
* @param modifierIndex The index of the modifier value
*/
void Zone::setAnimationModifier(int modifierIndex) {
  switch(currentAnimation) {
    case STATIC:
      _staticColorIndex = modifierIndex;
      setAllLEDs(STATIC_COLORS[_staticColorIndex]);
      break;
    case FADE:
      _fadeStepIndex = modifierIndex;
      break;
    default:
      // No modifier for the currently selected animation
      break;
  }
}

void Zone::cycleAnimationType() {
  ANIMATION_TYPE nextType = animationTypes[(currentAnimation + 1) % (sizeof(animationTypes) / sizeof(animationTypes[0]))];
  setAnimationType(nextType);
}

/**
 * Cycles the current animation to the the next modifier
 */
void Zone::cycleAnimationModifier() {
  switch (currentAnimation) {
    case STATIC:
      _staticColorIndex = (_staticColorIndex + 1) % (sizeof(STATIC_COLORS) / sizeof(STATIC_COLORS[0]));
      setAllLEDs(STATIC_COLORS[_staticColorIndex]);
      break;
    case CUSTOM:
      _customTypeIndex = (_customTypeIndex + 1) % (sizeof(STATIC_COLORS) / sizeof(STATIC_COLORS[0]));
      _setCustom(CUSTOM_TYPES[_customTypeIndex]);
      break;
    case FADE:
      _fadeStepIndex = (_fadeStepIndex + 1) % (sizeof(FADE_STEP_MS) / sizeof(FADE_STEP_MS[0]));
      break;
    default:
      // No modifier for the currently selected animation
      break;
  }
}

/**
* Fades each color (R/G/B) in and out, sequentially
*/
void Zone::_animateFadeRGB() {
  unsigned long now = millis();
  if (now - _lastAnimStepMs < FADE_STEP_MS[_fadeStepIndex]) {
    return;
  }
  _lastAnimStepMs = now;
  // Turn off all LEDs first
  setAllLEDs(0, 0, 0);

  // Calculate brightness as a percentage of the current brightness setting
  float normalized = _fadePercent / 100.0;
  int brightness = normalized * _currentBrightness;

  switch (_fadeColorIndex) {
    case 0:  // red
      setAllLEDs(brightness, 0, 0);
      break;
    case 1:  // green
      setAllLEDs(0, brightness, 0);
      break;
    case 2:  // blue
      setAllLEDs(0, 0, brightness);
      break;
    default:
      // no color
      break;
  }

  _fadePercent += _fadeDir;
  if (_fadePercent >= 100) {
    _fadeDir = -1;
  } else if (_fadePercent <= 0) {
    _fadeDir = 1;
    _fadeColorIndex = (_fadeColorIndex + 1) % 3;
  }
}

// /**
// * Sets the brightness value of single LED pin to the specified percentage value
// * @param ledPin The pin number of the LED to set the brightness of
// * @param percent The brightness percentage value (0-100)
// */
// void Zone::_setLEDPinBrightness(int ledPin, int percent) {
//   // Constrain percentage to 0-100
//   percent = constrain(percent, 0, 100);

//   // set brightness level using gamma correction
//   float gamma = 2.2;
//   float normalized = percent / 100.0;
//   int brightness = pow(normalized, gamma) * 255;
//   analogWrite(ledPin, brightness);
// }

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param rValue the brightness value of the red channel
* @param gValue the brightness value of the green channel
* @param bValue the brightness value of the blue channel
*/
void Zone::setAllLEDs(uint8_t rValue, uint8_t gValue, uint8_t bValue) {
  // Should be overridden
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param color the color to set for all LEDs
*/
void Zone::setAllLEDs(RGB_t &color) {
  setAllLEDs(color.r, color.g, color.b);
}

/**
 * Set the color of an addressable RGB LED
 * @param led the FastLED CRGB array
 * @param color the color to set for the LED
 * @param index the index of the CRGB array corresponding to the LED
 */
void Zone::_setColor(CRGB* leds, RGB_t &color, int index) {
  leds[index].setRGB(color.r, color.g, color.b);
}

/**
 * Set the color for all the LEDs in the CRGB array
 * @param led the FastLED CRGB array
 * @param color the color to set for the LEDs
 * @param index the number of LEDs in the CRGB array
 */
void Zone::_setAllCRGB(CRGB* leds, RGB_t &color, int count) {
  for (int i = 0; i < count; i++) {
    _setColor(leds, color, i);
  }
}

/**
 * Set the color for the specefied addressable RGB LEDs
 * @param led the FastLED CRGB array
 * @param color the color to set for the LEDs
 * @param indexes the indexes of the CRGB array corresponding to the LEDs
 * @param size the size of the CRGB array
 */
void Zone::_setColor(CRGB* leds, RGB_t &color, int* indexes, int size) {
  for (int i = 0; i < size; i++) {
    int index = indexes[i];
    leds[index].setRGB(color.r, color.g, color.b);
  }
}

/**
 * Sets the zone to the specified custom lighting pattern
 * @param type the custom type
 */
void Zone::_setCustom(CustomType &type) {
  switch (type) {
    case SF_TURBO:
      _setSFTurbo();
      break;
    default:
      // No custom type
  }
}

/**
 * Sets the SF Turbo custom lighting pattern
 */
void Zone::_setSFTurbo() {
  // Should be overridden
}

/**
 * Processes the custom lighting animation
 */
void Zone::_animateCustom() {
  // Should be overridden
}

/**
 * Resets all animations to their initial state
 */
void Zone::reset() {
  _lastAnimStepMs = 0;
  _fadePercent = 0;
  _fadeDir = 1;
  _fadeColorIndex = 0;
  _switchAnimationActive = false;
}