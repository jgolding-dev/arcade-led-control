#include <zone.h>

Options::Options(int brightness)
  : Zone(brightness) {}

void Options::setup() {
  animationTypes = OPTIONS_ANIMATION_TYPES;
  currentAnimation = CUSTOM;
  FastLED.addLeds<OPTIONS_BUTTONS_LED_TYPE, OPTIONS_BUTTONS_DATA_PIN, GRB>(_leds, OPTIONS_BUTTONS_LED_COUNT);
  FastLED.setBrightness(_currentBrightness);

  // Overlay buttons default to set colors
  _setLED(_leds, RGB_GREEN, HOME_LED);
  _setLED(_leds, RGB_BLUE, EXTRA1_LED);
}

/**
* Puts the zone in an idle state
*/
void Options::idle() {
  if (currentAnimation != IDLE) {
    _setLED(_leds, RGB_BLACK, HOME_LED);
    _setLED(_leds, RGB_BLACK, EXTRA1_LED);
    setAnimationType(IDLE);
  }
}

/**
* Puts the zone in a wake state
*/
void Options::wake() {
  if (currentAnimation == IDLE) {
    _setLED(_leds, RGB_GREEN, HOME_LED);
    _setLED(_leds, RGB_BLUE, EXTRA1_LED);
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
  for (int i = 2; i < OPTIONS_BUTTONS_LED_COUNT; i++) { // Exclude HOME buttons
    _leds[i].setRGB(rValue, gValue, bValue);
  }
  FastLED.show();
}

/**
* Applies the SF Turbo custom lighting pattern to the zone
*/
void Options::_setSFTurbo() {
  Zone::setAllZone(RGB_WHITE);
}