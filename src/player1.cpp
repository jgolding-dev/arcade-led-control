#include <zone.h>

Player1::Player1(int brightness)
  : Zone(brightness) {}

void Player1::setup() {
  animationTypes = ANIMATION_TYPES;
  currentAnimation = CUSTOM;
  FastLED.addLeds<ACTION_BUTTONS_LED_TYPE, PLAYER1_BUTTONS_DATA_PIN, ACTION_BUTTONS_LED_COLOR_ORDER>(_buttonLeds, ACTION_BUTTONS_LED_COUNT);
  FastLED.addLeds<JOYSTICK_RING_LED_TYPE, PLAYER1_JOYSTICK_DATA_PIN, JOYSTICK_RING_LED_COLOR_ORDER>(_joystickLeds, 0, JOYSTICK_RING_LED_COUNT);

  // The balltop LEDs are connected in series after the joystick ring LEDs, so we start the data at the end of the joystick ring LED data
  FastLED.addLeds<JOYSTICK_BALLTOP_LED_TYPE, PLAYER1_JOYSTICK_DATA_PIN, JOYSTICK_BALLTOP_LED_COLOR_ORDER>(_balltopLeds, JOYSTICK_RING_LED_COUNT, JOYSTICK_BALLTOP_LED_COUNT);

  FastLED.setBrightness(_currentBrightness);
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param rValue the brightness value of the red channel
* @param gValue the brightness value of the green channel
* @param bValue the brightness value of the blue channel
*/
void Player1::setAllZone(uint8_t rValue, uint8_t gValue, uint8_t bValue) {
  for (int i = 0; i < ACTION_BUTTONS_LED_COUNT; i++) {
    _buttonLeds[i].setRGB(rValue, gValue, bValue);
  }
  for (int i = 0; i < JOYSTICK_RING_LED_COUNT; i++) {
    _joystickLeds[i].setRGB(rValue, gValue, bValue);
  }
  for (int i = 0; i < JOYSTICK_BALLTOP_LED_COUNT; i++) {
    _balltopLeds[i].setRGB(rValue, gValue, bValue);
  }
  FastLED.show();
}

/**
* Applies the SF Turbo custom lighting pattern to the zone
*/
void Player1::_setSFTurbo() {
  Serial.println("Setting Player 1 SF_Turbo");

  Zone::setAllZone(RGB_BLACK);

  // joystick ring
  for (int i = 0; i < JOYSTICK_RING_LED_COUNT; i++) {
    _setLED(_joystickLeds, RGB_BLUE, i);
  }
  // balltop
  for (int i = 0; i < JOYSTICK_BALLTOP_LED_COUNT; i++) {
    _setLED(_balltopLeds, RGB_BLUE, i);
  }

  // buttons
  uint8_t light[SINGLE_BTN_LED_COUNT * 2];
  memcpy(light, BTN1_LEDs, SINGLE_BTN_LED_COUNT * sizeof(uint8_t));
  memcpy(light + SINGLE_BTN_LED_COUNT, BTN3_LEDs, SINGLE_BTN_LED_COUNT * sizeof(uint8_t));

  uint8_t medium[SINGLE_BTN_LED_COUNT * 2];
  memcpy(medium, BTN2_LEDs, SINGLE_BTN_LED_COUNT * sizeof(uint8_t));
  memcpy(medium + SINGLE_BTN_LED_COUNT, BTN4_LEDs, SINGLE_BTN_LED_COUNT * sizeof(uint8_t));
  
  uint8_t heavy[SINGLE_BTN_LED_COUNT * 2];
  memcpy(heavy, R1_LEDs, SINGLE_BTN_LED_COUNT * sizeof(uint8_t));
  memcpy(heavy + SINGLE_BTN_LED_COUNT, R2_LEDs, SINGLE_BTN_LED_COUNT * sizeof(uint8_t));
  
  uint8_t special[SINGLE_BTN_LED_COUNT * 2];
  memcpy(special, L1_LEDs, SINGLE_BTN_LED_COUNT * sizeof(uint8_t));
  memcpy(special + SINGLE_BTN_LED_COUNT, L2_LEDs, SINGLE_BTN_LED_COUNT * sizeof(uint8_t));

  Zone::setLEDs(_buttonLeds, RGB_RED, light, SINGLE_BTN_LED_COUNT * 2);
  Zone::setLEDs(_buttonLeds, RGB_BLUE, medium, SINGLE_BTN_LED_COUNT * 2);
  Zone::setLEDs(_buttonLeds, RGB_GREEN, heavy, SINGLE_BTN_LED_COUNT * 2);
  Zone::setLEDs(_buttonLeds, RGB_YELLOW, special, SINGLE_BTN_LED_COUNT * 2);

  FastLED.show();
}

/**
 * Fill the zone with the same hue and maximum saturation/brightness
 * @param hue the hue value for the color to fill the zone with
 */
void Player1::fillSolid(uint8_t hue) {
  fill_solid(_joystickLeds, JOYSTICK_RING_LED_COUNT, CHSV(hue, 255, 255));
  fill_solid(_balltopLeds, JOYSTICK_BALLTOP_LED_COUNT, CHSV(hue, 255, 255));
  fill_solid(_buttonLeds, ACTION_BUTTONS_LED_COUNT, CHSV(hue, 255, 255));
}

/**
 * Fill the zone with a rainbow gradient
 * @param gHueValue the gradient value for the rainbow
 */
void Player1::fillRainbow(uint8_t gHueValue) {
  // The '7' at the end defines the color difference between adjacent LEDs
  fill_rainbow(_joystickLeds, JOYSTICK_RING_LED_COUNT, gHueValue, 7);
  fill_rainbow(_balltopLeds, JOYSTICK_BALLTOP_LED_COUNT, gHueValue, 7);
  fill_rainbow(_buttonLeds, ACTION_BUTTONS_LED_COUNT, gHueValue, 7);
}