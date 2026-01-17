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
  setAllLEDs(0, 0, 0);
  switch (animType) {
    case STATIC:
      _setColor(STATIC_COLORS[_staticColorIndex]);
      break;
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
      _setColor(STATIC_COLORS[_staticColorIndex]);
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
      _setColor(STATIC_COLORS[_staticColorIndex]);
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

/**
 * Sets all LEDs to the specified hex color value
 * @param color the hex color value to set the LEDs to
 */
void Zone::_setColor(uint32_t color) {
  // Serial.println("In Parent _setColor");
  // delay(50);
  int r = (color >> 16) & 0xFF;
  int g = (color >> 8) & 0xFF;
  int b = color & 0xFF;
  setAllLEDs(r, g, b);
}

/**
* Sets the brightness value of single LED pin to the specified percentage value
* @param ledPin The pin number of the LED to set the brightness of
* @param percent The brightness percentage value (0-100)
*/
void Zone::_setLEDPinBrightness(int ledPin, int percent) {
  // Constrain percentage to 0-100
  percent = constrain(percent, 0, 100);

  // set brightness level using gamma correction
  float gamma = 2.2;
  float normalized = percent / 100.0;
  int brightness = pow(normalized, gamma) * 255;
  analogWrite(ledPin, brightness);
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param rValue the brightness value of the red channel
* @param gValue the brightness value of the green channel
* @param bValue the brightness value of the blue channel
*/
void Zone::setAllLEDs(int rValue, int gValue, int bValue) {
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