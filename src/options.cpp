#include <zone.h>

Options::Options(int brightness, OptionsInputProcessor& inputProcessor)
  : Zone(brightness),
    _inputProcessor(&inputProcessor) {}

void Options::setup() {
  animationTypes = ANIMATION_TYPES;
  currentAnimation = CUSTOM;
  FastLED.addLeds<OPTIONS_BUTTONS_LED_TYPE, OPTIONS_BUTTONS_DATA_PIN, OPTIONS_BUTTONS_LED_COLOR_ORDER>(_leds, OPTIONS_LED_ZONE_COUNT);
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
  for (int i = 0; i < OPTIONS_LED_ZONE_COUNT; i++) {
    _leds[i].setRGB(rValue, gValue, bValue);
  }
  showLEDs();
}

/**
* Applies the SF Turbo custom lighting pattern to the zone
*/
void Options::_setSFTurbo() {
  int i = 0;
  while (i < OPTIONS_LED_ZONE_COUNT) {
    if (i == HOME_LEDs[0]) {
      Zone::setLEDs(_leds, RGB_GREEN, HOME_LEDs, OPTIONS_BTN_LED_COUNT);
      i += OPTIONS_BTN_LED_COUNT;
    }
    else if (i == EXTRA1_LEDs[0]) {
      Zone::setLEDs(_leds, RGB_BLUE, EXTRA1_LEDs, OPTIONS_BTN_LED_COUNT);
      i += OPTIONS_BTN_LED_COUNT;
    }
    else {
      Zone::setLED(_leds, RGB_WHITE, i);
      i++;
    }
  }
  showLEDs();
}

/**
* Applies the Red_vs_Blue custom lighting pattern to the zone
*/
void Options::_setRedVsBlue() {
  // Player 1
  Zone::setLEDs(_leds, RGB_BLUE, P1_SELECT_LEDs, OPTIONS_BTN_LED_COUNT);
  Zone::setLEDs(_leds, RGB_BLUE, P1_START_LEDs, OPTIONS_BTN_LED_COUNT);
  
  // Player 2
  Zone::setLEDs(_leds, RGB_RED, P2_SELECT_LEDs, OPTIONS_BTN_LED_COUNT);
  Zone::setLEDs(_leds, RGB_RED, P2_START_LEDs, OPTIONS_BTN_LED_COUNT);

  // Guide
  Zone::setLEDs(_leds, RGB_WHITE, HOME_LEDs, OPTIONS_BTN_LED_COUNT);
  Zone::setLEDs(_leds, RGB_WHITE, EXTRA1_LEDs, OPTIONS_BTN_LED_COUNT);
  showLEDs();
}

/**
 * Fill the zone with the same hue, saturation, and brightness
 * @param hue the hue value for the color to fill the zone with
 */
void Options::fillSolid(uint8_t hue) {
  fill_solid(_leds, OPTIONS_LED_ZONE_COUNT, CHSV(hue, 255, 255));
}

/**
 * Fill the zone with a rainbow gradient=
 * @param gHueValue the gradient value for the rainbow
 */
void Options::fillRainbow(uint8_t gHueValue) {
  // The '7' at the end defines the color difference between adjacent LEDs
  fill_rainbow(_leds, OPTIONS_LED_ZONE_COUNT, gHueValue, 7);
}

/**
 * Process the reactive animation for the zone
 */
void Options::animateReactive() {
  Zone::setAllZone(RGB_BLACK);
  for (uint8_t i = 0; i < OPTIONS_INPUT_COUNT; i++) {
    if (_inputProcessor->isButtonActive(i)) {
      Zone::setLEDs(_leds, RGB_WHITE, OPTIONS_MAP[i].ledIndices, OPTIONS_BTN_LED_COUNT);
    }
  }
  showLEDs();
}