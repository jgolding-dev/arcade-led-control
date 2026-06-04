#include <zone.h>

Player1::Player1(int brightness)
  : Zone(brightness) {}

void Player1::setup() {
  previousAnimation = CUSTOM;
  currentAnimation = IDLE;
  _staticColorIndex = 0;
  _fadeStepIndex = 1;  // FADE_STEP_NORMAL
  _fadeColorIndex = 0;
  FastLED.addLeds<PLAYER1_BUTTONS_LED_TYPE, PLAYER1_BUTTONS_DATA_PIN, GRB>(_buttonLeds, PLAYER1_BUTTONS_LED_COUNT);
  FastLED.addLeds<PLAYER1_JOYSTICK_LED_TYPE, PLAYER1_JOYSTICK_DATA_PIN, GRB>(_joystickLeds, PLAYER1_JOYSTICK_LED_COUNT);
  FastLED.setBrightness(_currentBrightness);
}

void Player1::_applyAnimation(ANIMATION_TYPE animType) {
  _animations[animType]->apply(_buttonLeds, PLAYER1_BUTTONS_LED_COUNT);
  _animations[animType]->apply(_joystickLeds, PLAYER1_JOYSTICK_LED_COUNT);
  FastLED.show();
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param rValue the brightness value of the red channel
* @param gValue the brightness value of the green channel
* @param bValue the brightness value of the blue channel
*/
void Player1::setAllZone(uint8_t rValue, uint8_t gValue, uint8_t bValue) {
  for (int i = 0; i < PLAYER1_BUTTONS_LED_COUNT; i++) {
    _buttonLeds[i].setRGB(rValue, gValue, bValue);
  }
  for (int i = 0; i < PLAYER1_JOYSTICK_LED_COUNT; i++) {
    _joystickLeds[i].setRGB(rValue, gValue, bValue);
  }
  FastLED.show();
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
*/
void Player1::_setSFTurbo() {
  Serial.println("Setting Player 1 SF_Turbo");

  Zone::setAllZone(RGB_BLACK);

  // joystick
  for (int i = 0; i < PLAYER1_JOYSTICK_LED_COUNT; i++) {
    _setLED(_joystickLeds, RGB_BLUE, i);
  }

  // buttons
  int light[] = {B1_LED, (B1_LED + 1), B3_LED, (B3_LED + 1) };
  int medium[] = { B2_LED, (B2_LED + 1), B4_LED, (B4_LED + 1) };
  int heavy[] = { R1_LED, (R1_LED + 1), R2_LED, (R2_LED + 1) };
  int special[] = { L1_LED, (L1_LED + 1), L2_LED, (L2_LED + 1) };

  setLEDs(_buttonLeds, RGB_RED, light, 4);
  setLEDs(_buttonLeds, RGB_BLUE, medium, 4);
  setLEDs(_buttonLeds, RGB_GREEN, heavy, 4);
  setLEDs(_buttonLeds, RGB_YELLOW, special, 4);

  FastLED.show();
}