#include <zone.h>

Zone::Zone(int brightness)
  : _currentBrightness(brightness) {}

void Zone::setup() {
  _fadeStepIndex = 1;  // FADE_STEP_NORMAL
  _fadeColorIndex = 0;
  _zoneSwitchBlinkDir = 1;
  _switchAnimationActive = false;
  _lastZoneSwitchAnimStepMs = 0;
  _colorShiftSpeedIndex = 1; // COLOR_SHIFT_SPEED_NORMAL
  _rainbowShiftSpeedIndex = 1; // COLOR_SHIFT_SPEED_NORMAL
  _customTypeIndex = 0;
  _staticColorIndex = 0;
  _blendType = LINEARBLEND;
  _blendIndex = 0;
  _gHue = 0;
}

/**
 * Advances to the next frame of the current animation
 */
void Zone::process() {
  if (_switchAnimationActive) {
    _processZoneSwitchAnimation();
    return;
  }
  switch (currentAnimation) {
    case FADE:
      _animateFadeRGB();
      break;
    // case CUSTOM:
    //   _animateCustom();
    //   break;
    case COLOR_SHIFT:
      _animateColorShift();
      break;
    case RAINBOW:
      _animateRainbow();
      break;
    default:
      // No animation
      break;
  }
}

/**
 * Display a white blinking LED animation to indicate a zone switch is occurring
 */
void Zone::_processZoneSwitchAnimation() {
  unsigned long now = millis();
  if (now - _lastZoneSwitchAnimStepMs < ZONE_SWITCH_ANIMATION_STEP_MS) {
    return;
  }
  _lastZoneSwitchAnimStepMs = now;

  // Blink white
  if (_zoneSwitchBlinkDir == 1) {
    setAllZone(RGB_WHITE);
    _zoneSwitchBlinkDir = -1;
  } else {
    setAllZone(RGB_BLACK);
    _zoneSwitchBlinkDir = 1;
  }
}

void Zone::setMasterBrightness(int value) {
  _currentBrightness = value;
  FastLED.setBrightness(_currentBrightness);
  showLEDs();
}

/**
* Set the zone switch animation to run at the next frame
*/
void Zone::startZoneSwitchAnimation() {
  _switchAnimationActive = true;
  setAllZone(RGB_BLACK);
  _lastZoneSwitchAnimStepMs = millis();
}

/**
 * Stop the zone switch animation
 */
void Zone::endZoneSwitchAnimation() {
  _switchAnimationActive = false;
  _zoneSwitchBlinkDir = 1;
  _lastZoneSwitchAnimStepMs = 0;
  setAnimationType(currentAnimation);
}

/**
 * Whether the zone switch animation is currently active
 * @returns true if the zone switch animation is active. Otherwise, false.
 */
bool Zone::isZoneSwitchActive() {
  return _switchAnimationActive;
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
  setAllZone(RGB_BLACK);
  switch (animType) {
    case STATIC:
      setAllZone(COLORS[_staticColorIndex]);
      break;
    case CUSTOM:
      applyCustom(CUSTOM_TYPES[_customTypeIndex]);
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
      setAllZone(COLORS[_staticColorIndex]);
      break;
    case CUSTOM:
      _customTypeIndex = modifierIndex;
      applyCustom(CUSTOM_TYPES[_customTypeIndex]);
      break;
    case FADE:
      _fadeStepIndex = modifierIndex;
      break;
    case COLOR_SHIFT:
      _colorShiftSpeedIndex = modifierIndex;
      break;
    case RAINBOW:
      _rainbowShiftSpeedIndex = modifierIndex;
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
      _staticColorIndex = (_staticColorIndex + 1) % (sizeof(COLORS) / sizeof(COLORS[0]));
      setAllZone(COLORS[_staticColorIndex]);
      break;
    case CUSTOM:
      _customTypeIndex = (_customTypeIndex + 1) % (sizeof(CUSTOM_TYPES) / sizeof(CUSTOM_TYPES[0]));
      applyCustom(CUSTOM_TYPES[_customTypeIndex]);
      break;
    case COLOR_SHIFT:
      _colorShiftSpeedIndex = (_colorShiftSpeedIndex + 1) % (sizeof(COLOR_SHIFT_SPEEDS) / sizeof(COLOR_SHIFT_SPEEDS[0]));
      break;
    case RAINBOW:
      _rainbowShiftSpeedIndex = (_rainbowShiftSpeedIndex + 1) % (sizeof(COLOR_SHIFT_SPEEDS) / sizeof(COLOR_SHIFT_SPEEDS[0]));
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
  if (now - _lastFadeAnimStepMs < FADE_STEP_MS[_fadeStepIndex]) {
    return;
  }
  _lastFadeAnimStepMs = now;
  // Turn off all LEDs first
  setAllZone(0, 0, 0);

  // Calculate brightness as a percentage of the current brightness setting
  float normalized = _fadePercent / 100.0;
  uint8_t brightness = normalized * _currentBrightness;

  switch (_fadeColorIndex) {
    case 0:  // red
      setAllZone(brightness, 0, 0);
      break;
    case 1:  // green
      setAllZone(0, brightness, 0);
      break;
    case 2:  // blue
      setAllZone(0, 0, brightness);
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
 * animate the color shift animation for the zone
 */
void Zone::_animateColorShift() {
  // Fill the strip with a solid color that shifts over time
  
  uint8_t hue = beat8(COLOR_SHIFT_SPEEDS[_colorShiftSpeedIndex]); // speed (bpm) of the color shift animation

  fillSolid(hue);
  
  showLEDs();
}

/**
 * animate the color blend animation for the zone
 */
void Zone::_animateRainbow() {
  // Fill the strip with a rainbow gradient that shifts over time
  
  uint8_t hue = beat8(COLOR_SHIFT_SPEEDS[_rainbowShiftSpeedIndex]); // speed (bpm) of the rainbow color shift animation

  fillRainbow(hue);
  
  showLEDs();  
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param rValue the brightness value of the red channel
* @param gValue the brightness value of the green channel
* @param bValue the brightness value of the blue channel
*/
void Zone::setAllZone(uint8_t rValue, uint8_t gValue, uint8_t bValue) {
  // Should be overridden
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param color the color to set for all LEDs
*/
void Zone::setAllZone(const RGB_t &color) {
  setAllZone(color.r, color.g, color.b);
}

/**
 * Set the color of an addressable RGB LED
 * @param led the FastLED CRGB array
 * @param color the color to set for the LED
 * @param index the index of the CRGB array corresponding to the LED
 */
void Zone::setLED(CRGB* leds, const RGB_t &color, int index) {
  leds[index].setRGB(color.r, color.g, color.b);
}

/**
 * Set the color for the specefied addressable RGB LEDs
 * @param led the FastLED CRGB array
 * @param color the color to set for the LEDs
 * @param indexes the indexes of the CRGB array corresponding to the LEDs
 * @param size the size of the CRGB array
 */
void Zone::setLEDs(CRGB* leds, const RGB_t &color, uint8_t* indexes, int size) {
  for (int i = 0; i < size; i++) {
    int index = indexes[i];
    setLED(leds, color, index);
  }
}

/**
 * Set the color for the specefied addressable RGB LEDs
 * @param led the FastLED CRGB array
 * @param color the color to set for the LEDs
 * @param indexes the indexes of the CRGB array corresponding to the LEDs
 * @param size the size of the CRGB array
 */
void Zone::setLEDs(CRGB* leds, const RGB_t &color, const uint8_t* indexes, int size) {
  for (int i = 0; i < size; i++) {
    int index = indexes[i];
    setLED(leds, color, index);
  }
}

/**
 * Set the color for all the LEDs in the CRGB array
 * @param led the FastLED CRGB array
 * @param color the color to set for the LEDs
 * @param index the number of LEDs in the CRGB array
 */
void Zone::setLEDs(CRGB* leds, const RGB_t &color, int count) {
  for (int i = 0; i < count; i++) {
    setLED(leds, color, i);
  }
}

/**
 * Sets the zone to the specified custom lighting pattern
 * @param type the custom type
 */
void Zone::applyCustom(const CustomType &type) {
  switch (type) {
    case SF_TURBO:
      _setSFTurbo();
      break;
    case RED_VS_BLUE:
      _setRedVsBlue();
    default:
      // No custom type
      break;
  }
}

/**
 * Directs FastLED to update its controllers with the current LED states
 */
void Zone::showLEDs() {
  FastLED.show();
}

/**
 * Resets animations to their initial state
 */
void Zone::reset() {
  _lastFadeAnimStepMs = 0;
  _fadePercent = 0;
  _fadeDir = 1;
  _fadeColorIndex = 0;
  _switchAnimationActive = false;
  _zoneSwitchBlinkDir = 1;
  _lastZoneSwitchAnimStepMs = 0;
}