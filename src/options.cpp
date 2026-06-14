#include <zone.h>

Options::Options(int brightness)
  : Zone(brightness) {}

void Options::setup() {
  animationTypes = ANIMATION_TYPES;
  currentAnimation = CUSTOM;
  FastLED.addLeds<OPTIONS_BUTTONS_LED_TYPE, OPTIONS_BUTTONS_DATA_PIN, OPTIONS_BUTTONS_LED_COLOR_ORDER>(_leds, OPTIONS_BUTTONS_LED_COUNT);
  FastLED.setBrightness(_currentBrightness);
}

/**
* Puts the zone in an idle state
*/
void Options::idle() {
  if (currentAnimation != IDLE) {
    setAnimationType(IDLE);
  }
}

/**
* Puts the zone in a wake state
*/
void Options::wake() {
  if (currentAnimation == IDLE) {
    setAnimationType(previousAnimation);
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
  for (int i = 0; i < OPTIONS_BUTTONS_LED_COUNT; i++) {
    _leds[i].setRGB(rValue, gValue, bValue);
  }
  showLEDs();
}

/**
* Applies the SF Turbo custom lighting pattern to the zone
*/
void Options::_setSFTurbo() {
  Zone::setAllZone(RGB_WHITE);
}

/**
 * Fill the zone with the same hue, saturation, and brightness
 * @param hue the hue value for the color to fill the zone with
 */
void Options::fillSolid(uint8_t hue) {
  fill_solid(_leds, OPTIONS_BUTTONS_LED_COUNT, CHSV(hue, 255, 255));
}

/**
 * Fill the zone with a rainbow gradient
 * @param gHueValue the gradient value for the rainbow
 */
void Options::fillRainbow(uint8_t gHueValue) {
  // The '7' at the end defines the color difference between adjacent LEDs
  fill_rainbow(_leds, OPTIONS_BUTTONS_LED_COUNT, gHueValue, 7);
}