#include <zone.h>

Player1::Player1(int brightness)
  : Zone(brightness) {}

void Player1::setup() {
  animationTypes = PLAYER1_ANIMATION_TYPES;
  previousAnimation = STATIC;
  currentAnimation = IDLE;
  _staticColorIndex = 0;
  _fadeStepIndex = 1;  // FADE_STEP_NORMAL
  _fadeColorIndex = 0;
  FastLED.addLeds<PLAYER1_BUTTONS_LED_TYPE, PLAYER1_BUTTONS_DATA_PIN, COLOR_ORDER>(_buttonLeds, PLAYER1_BUTTONS_LED_COUNT);
  FastLED.addLeds<PLAYER1_JOYSTICK_LED_TYPE, PLAYER1_JOYSTICK_DATA_PIN, COLOR_ORDER>(_joystickLeds, PLAYER1_JOYSTICK_LED_COUNT);
  FastLED.setBrightness(_currentBrightness);
}

/**
 * Advances to the next frame of the current animation
 */
void Player1::process() {
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
void Player1::cycleAnimationModifier() {
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
void Player1::setAllLEDs(uint8_t rValue, uint8_t gValue, uint8_t bValue) {
  Serial.println("Setting P1 LEDs");
  for (int i = 0; i < PLAYER1_BUTTONS_LED_COUNT; i++) {
    _buttonLeds[i].r = rValue;
    _buttonLeds[i].g = gValue;
    _buttonLeds[i].b = bValue;
  }
  for (int i = 0; i < PLAYER1_JOYSTICK_LED_COUNT; i++) {
    _joystickLeds[i].r = rValue;
    _joystickLeds[i].g = gValue;
    _joystickLeds[i].b = bValue;
  }
  FastLED.show();
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
*/
void Player1::_setSFTurbo() {
  Serial.println("Setting Player 1 SF_Turbo");

  Zone::setAllLEDs(BLACK);

  // joystick
  for (int i = 0; i < PLAYER1_JOYSTICK_LED_COUNT; i++) {
    _setColor(_joystickLeds, BLUE, i);
  }

  // buttons
  int light[] = {B1_LED, (B1_LED + 1), B3_LED, (B3_LED + 1) };
  int medium[] = { B2_LED, (B2_LED + 1), B4_LED, (B4_LED + 1) };
  int heavy[] = { L1_LED, (L1_LED + 1), R1_LED, (R1_LED + 1) };
  int special[] = { L2_LED, (L2_LED + 1), R2_LED, (R2_LED + 1) };

  _setColor(_buttonLeds, RED, light, 4);
  _setColor(_buttonLeds, BLUE, medium, 4);
  _setColor(_buttonLeds, GREEN, heavy, 4);
  _setColor(_buttonLeds, YELLOW, special, 4);

  FastLED.show();
}