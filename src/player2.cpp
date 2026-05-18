#include <zone.h>

Player2::Player2(int brightness)
  : Zone(brightness) {}

void Player2::setup() {
  animationTypes = ANIMATION_TYPES;
  currentAnimation = CUSTOM;
  FastLED.addLeds<PLAYER2_BUTTONS_LED_TYPE, PLAYER2_BUTTONS_DATA_PIN, GRB>(_buttonLeds, PLAYER2_BUTTONS_LED_COUNT);
  FastLED.addLeds<PLAYER2_JOYSTICK_LED_TYPE, PLAYER2_JOYSTICK_DATA_PIN, GRB>(_joystickLeds, PLAYER2_JOYSTICK_LED_COUNT);
  FastLED.setBrightness(_currentBrightness);
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param rValue the brightness value of the red channel
* @param gValue the brightness value of the green channel
* @param bValue the brightness value of the blue channel
*/
void Player2::setAllZone(uint8_t rValue, uint8_t gValue, uint8_t bValue) {
  Serial.println("Setting P2 LEDs");
  for (int i = 0; i < PLAYER2_BUTTONS_LED_COUNT; i++) {
    _buttonLeds[i].r = rValue;
    _buttonLeds[i].g = gValue;
    _buttonLeds[i].b = bValue;
  }
  for (int i = 0; i < PLAYER2_JOYSTICK_LED_COUNT; i++) {
    _joystickLeds[i].r = rValue;
    _joystickLeds[i].g = gValue;
    _joystickLeds[i].b = bValue;
  }
  FastLED.show();
}

/**
* Applies the SF Turbo custom lighting pattern to the zone
*/
void Player2::_setSFTurbo() {
  Serial.println("Setting Player 1 SF_Turbo");

  Zone::setAllZone(RGB_BLACK);

  // joystick
  for (int i = 0; i < PLAYER2_JOYSTICK_LED_COUNT; i++) {
    Zone::_setLED(_joystickLeds, RGB_BLUE, i);
  }

  // buttons
  int light[SINGLE_BTN_LED_COUNT * 2];
  memcpy(light, BTN1_LEDs, SINGLE_BTN_LED_COUNT * sizeof(int));
  memcpy(light + SINGLE_BTN_LED_COUNT, BTN3_LEDs, SINGLE_BTN_LED_COUNT * sizeof(int));

  int medium[SINGLE_BTN_LED_COUNT * 2];
  memcpy(medium, BTN2_LEDs, SINGLE_BTN_LED_COUNT * sizeof(int));
  memcpy(medium + SINGLE_BTN_LED_COUNT, BTN4_LEDs, SINGLE_BTN_LED_COUNT * sizeof(int));
  
  int heavy[SINGLE_BTN_LED_COUNT * 2];
  memcpy(heavy, R1_LEDs, SINGLE_BTN_LED_COUNT * sizeof(int));
  memcpy(heavy + SINGLE_BTN_LED_COUNT, R2_LEDs, SINGLE_BTN_LED_COUNT * sizeof(int));
  
  int special[SINGLE_BTN_LED_COUNT * 2];
  memcpy(special, L1_LEDs, SINGLE_BTN_LED_COUNT * sizeof(int));
  memcpy(special + SINGLE_BTN_LED_COUNT, L2_LEDs, SINGLE_BTN_LED_COUNT * sizeof(int));

  setLEDs(_buttonLeds, RGB_RED, light, SINGLE_BTN_LED_COUNT * 2);
  setLEDs(_buttonLeds, RGB_BLUE, medium, SINGLE_BTN_LED_COUNT * 2);
  setLEDs(_buttonLeds, RGB_GREEN, heavy, SINGLE_BTN_LED_COUNT * 2);
  setLEDs(_buttonLeds, RGB_YELLOW, special, SINGLE_BTN_LED_COUNT * 2);

  FastLED.show();
}