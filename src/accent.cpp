#include <zone.h>

Accent::Accent(int brightness)
  : Zone(brightness) {}

void Accent::setup() {
  animationTypes = ANIMATION_TYPES;
  currentAnimation = CUSTOM;
  FastLED.addLeds<ACCENT_LED_TYPE, ACCENT_DATA_PIN, GRB>(_leds, ACCENT_LED_COUNT);
  FastLED.setBrightness(_currentBrightness);
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param rValue the brightness value of the red channel
* @param gValue the brightness value of the green channel
* @param bValue the brightness value of the blue channel
*/
void Accent::setAllZone(uint8_t rValue, uint8_t gValue, uint8_t bValue) {
  Serial.println("Setting Accent LEDs");
  for (int i = 0; i < ACCENT_LED_COUNT; i++) {
    _leds[i].r = rValue;
    _leds[i].g = gValue;
    _leds[i].b = bValue;
  }
  FastLED.show();
}