#include <zone.h>

Player2::Player2(int brightness)
  : Zone(brightness) {}

void Player2::setup() {
  animationTypes = PLAYER2_ANIMATION_TYPES;
  previousAnimation = STATIC;
  currentAnimation = IDLE;
  _staticColorIndex = 0;
  _fadeStepIndex = 1;  // FADE_STEP_NORMAL
  _fadeColorIndex = 0;
  FastLED.addLeds<PLAYER2_BUTTONS_LED_TYPE, PLAYER2_BUTTONS_DATA_PIN, COLOR_ORDER>(_buttonLeds, PLAYER2_BUTTONS_LED_COUNT);
  FastLED.addLeds<PLAYER2_JOYSTICK_LED_TYPE, PLAYER2_JOYSTICK_DATA_PIN, COLOR_ORDER>(_joystickLeds, PLAYER2_JOYSTICK_LED_COUNT);
  FastLED.setBrightness(_currentBrightness);
}

/**
 * Advances to the next frame of the current animation
 */
void Player2::process() {
  switch (currentAnimation) {
    case FADE:
      _animateFadeRGB();
      break;
    default:
      // No animation
      break;
  }
}

/**
 * Cycles the currently selected animation to the the next modifier
 */
void Player2::cycleAnimationModifier() {
  switch (currentAnimation) {
    case STATIC:
      _staticColorIndex = (_staticColorIndex + 1) % (sizeof(STATIC_COLORS) / sizeof(STATIC_COLORS[0]));
      Zone::setAllLEDs(STATIC_COLORS[_staticColorIndex]);
      break;
    case FADE:
      _fadeStepIndex = (_fadeStepIndex + 1) % (sizeof(FADE_STEP_MS) / sizeof(FADE_STEP_MS[0]));
      _lastAnimStepMs = 0;
      break;
    default:
      // No modifier
      break;
  }
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param rValue the brightness value of the red channel
* @param gValue the brightness value of the green channel
* @param bValue the brightness value of the blue channel
*/
void Player2::setAllLEDs(uint8_t rValue, uint8_t gValue, uint8_t bValue) {
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
* Sets the brightness level (%) of all LED channels (R/G/B)
*/
void Player2::_setSFTurbo() {
  Serial.println("Setting Player 1 SF_Turbo");

  Zone::setAllLEDs(BLACK);

  // joystick
  for (int i = 0; i < PLAYER2_JOYSTICK_LED_COUNT; i++) {
    Zone::_setColor(_joystickLeds, BLUE, i);
  }

  // buttons
  int light[] = {P2_BTN1, (P2_BTN1 + 1), P2_BTN3, (P2_BTN3 + 1) };
  int medium[] = { P2_BTN2, (P2_BTN2 + 1), P2_BTN4, (P2_BTN4 + 1) };
  int heavy[] = { P2_L1, (P2_L1 + 1), P2_R1, (P2_R1 + 1) };
  int special[] = { P2_L2, (P2_L2 + 1), P2_R2, (P2_R2 + 1) };

  _setColor(_buttonLeds, RED, light, 4);
  _setColor(_buttonLeds, BLUE, medium, 4);
  _setColor(_buttonLeds, GREEN, heavy, 4);
  _setColor(_buttonLeds, YELLOW, special, 4);

  FastLED.show();
}