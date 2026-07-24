#include <zone.h>

Player2::Player2(int brightness, PlayerInputProcessor& inputProcessor
)
  : Zone(brightness),
    _inputProcessor(&inputProcessor) {}

void Player2::setup() {
  animationTypes = ANIMATION_TYPES;
  currentAnimation = CUSTOM;
  FastLED.addLeds<ACTION_BUTTONS_LED_TYPE, PLAYER2_BUTTONS_DATA_PIN, ACTION_BUTTONS_LED_COLOR_ORDER>(_buttonLeds, ACTION_LED_ZONE_COUNT);
  FastLED.addLeds<JOY_LED_TYPE, PLAYER2_JOY_DATA_PIN, JOY_LED_COLOR_ORDER>(_joystickOutputLeds, JOY_LED_ZONE_COUNT);
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param rValue the brightness value of the red channel
* @param gValue the brightness value of the green channel
* @param bValue the brightness value of the blue channel
*/
void Player2::setAllZone(uint8_t rValue, uint8_t gValue, uint8_t bValue) {
  for (int i = 0; i < ACTION_LED_ZONE_COUNT; i++) {
    _buttonLeds[i].setRGB(rValue, gValue, bValue);
  }
  for (int i = 0; i < JOY_LED_ZONE_COUNT; i++) {
    _joystickLogicalLeds[i].setRGB(rValue, gValue, bValue);
  }
  showLEDs();
}

/**
* Applies the SF Turbo custom lighting pattern to the zone
*/
void Player2::_setSFTurbo() {
  Serial.println("Setting Player 1 SF_Turbo");

  Zone::setAllZone(RGB_BLACK);

  // joystick ring and balltop
  for (int i = 0; i < JOY_LED_ZONE_COUNT; i++) {
    Zone::setLED(_joystickLogicalLeds, RGB_RED, i);
  }

  // buttons
  uint8_t light[ACTION_BTN_LED_COUNT * 2];
  memcpy(light, BTN1_LEDs, ACTION_BTN_LED_COUNT * sizeof(uint8_t));
  memcpy(light + ACTION_BTN_LED_COUNT, BTN3_LEDs, ACTION_BTN_LED_COUNT * sizeof(uint8_t));

  uint8_t medium[ACTION_BTN_LED_COUNT * 2];
  memcpy(medium, BTN2_LEDs, ACTION_BTN_LED_COUNT * sizeof(uint8_t));
  memcpy(medium + ACTION_BTN_LED_COUNT, BTN4_LEDs, ACTION_BTN_LED_COUNT * sizeof(uint8_t));
  
  uint8_t heavy[ACTION_BTN_LED_COUNT * 2];
  memcpy(heavy, R1_LEDs, ACTION_BTN_LED_COUNT * sizeof(uint8_t));
  memcpy(heavy + ACTION_BTN_LED_COUNT, R2_LEDs, ACTION_BTN_LED_COUNT * sizeof(uint8_t));
  
  uint8_t special[ACTION_BTN_LED_COUNT * 2];
  memcpy(special, L1_LEDs, ACTION_BTN_LED_COUNT * sizeof(uint8_t));
  memcpy(special + ACTION_BTN_LED_COUNT, L2_LEDs, ACTION_BTN_LED_COUNT * sizeof(uint8_t));

  Zone::setLEDs(_buttonLeds, RGB_RED, light, ACTION_BTN_LED_COUNT * 2);
  Zone::setLEDs(_buttonLeds, RGB_BLUE, medium, ACTION_BTN_LED_COUNT * 2);
  Zone::setLEDs(_buttonLeds, RGB_GREEN, heavy, ACTION_BTN_LED_COUNT * 2);
  Zone::setLEDs(_buttonLeds, RGB_YELLOW, special, ACTION_BTN_LED_COUNT * 2);

  showLEDs();
}

/**
* Applies the Red_vs_Blue custom lighting pattern to the zone
*/
void Player2::_setRedVsBlue() {
  Serial.println("Setting Player 2 Red_vs_Blue");

  Zone::setAllZone(RGB_RED);
  showLEDs();
}

/**
 * Fill the zone with the same hue, saturation, and brightness
 * @param hue the hue value for the color to fill the zone with
 */
void Player2::fillSolid(uint8_t hue) {
  fill_solid(_joystickLogicalLeds, JOY_LED_ZONE_COUNT, CHSV(hue, 255, 255));
  fill_solid(_buttonLeds, ACTION_LED_ZONE_COUNT, CHSV(hue, 255, 255));
}

/**
 * Fill the zone with a rainbow gradient
 * @param gHueValue the gradient value for the rainbowv
 */
void Player2::fillRainbow(uint8_t gHueValue) {
  // The '7' at the end defines the color difference between adjacent LEDs
  fill_rainbow(_joystickLogicalLeds, JOY_LED_ZONE_COUNT, gHueValue, 7);
  fill_rainbow(_buttonLeds, ACTION_LED_ZONE_COUNT, gHueValue, 7);
}

/**
 * Process the reactive animation for the zone
 */
void Player2::animateReactive() {
  RGB_t baseColor = REACTIVE_COLOR_PAIRS[_reactiveModifierIndex].base;
  RGB_t reactiveColor = REACTIVE_COLOR_PAIRS[_reactiveModifierIndex].reactive;

  Zone::setAllZone(baseColor);
  for (uint8_t i = 0; i < BUTTON_INPUT_COUNT; i++) {
    if (_inputProcessor->isButtonActive(i)) {
      Zone::setLEDs(_buttonLeds, reactiveColor, BUTTON_MAP[i].ledIndices, ACTION_BTN_LED_COUNT);
    }
  }

  for (uint8_t i = 0; i < JOYSTICK_INPUT_COUNT; i++) {
    if (_inputProcessor->isJoystickActive(i)) {
      uint8_t nextDirection = (i + 1) % JOYSTICK_INPUT_COUNT;
      uint8_t prevDirection = (i - 1) % JOYSTICK_INPUT_COUNT;
      if (_inputProcessor->isJoystickActive(nextDirection)) {
        switch(i) {
          case JOY_UP_GROUP_INDEX:
            Zone::setLEDs(_joystickLogicalLeds, reactiveColor, JOY_UP_RIGHT_LEDs, JOY_DIRECTION_LED_COUNT);
            break;
          case JOY_RIGHT_GROUP_INDEX:
            Zone::setLEDs(_joystickLogicalLeds, reactiveColor, JOY_DOWN_RIGHT_LEDs, JOY_DIRECTION_LED_COUNT);
            break;
          case JOY_DOWN_GROUP_INDEX:
            Zone::setLEDs(_joystickLogicalLeds, reactiveColor, JOY_DOWN_LEFT_LEDs, JOY_DIRECTION_LED_COUNT);
            break;
          case JOY_LEFT_GROUP_INDEX:
            Zone::setLEDs(_joystickLogicalLeds, reactiveColor, JOY_UP_LEFT_LEDs, JOY_DIRECTION_LED_COUNT);
            break;
        }
        break;
      }
      else if (_inputProcessor->isJoystickActive(prevDirection)) {
        switch (i) {
          case JOY_UP_GROUP_INDEX:
            Zone::setLEDs(_joystickLogicalLeds, reactiveColor, JOY_UP_LEFT_LEDs, JOY_DIRECTION_LED_COUNT);
            break;
          case JOY_RIGHT_GROUP_INDEX:
            Zone::setLEDs(_joystickLogicalLeds, reactiveColor, JOY_UP_RIGHT_LEDs, JOY_DIRECTION_LED_COUNT);
            break;
          case JOY_DOWN_GROUP_INDEX:
            Zone::setLEDs(_joystickLogicalLeds, reactiveColor, JOY_DOWN_RIGHT_LEDs, JOY_DIRECTION_LED_COUNT);
            break;
          case JOY_LEFT_GROUP_INDEX:
            Zone::setLEDs(_joystickLogicalLeds, reactiveColor, JOY_DOWN_LEFT_LEDs, JOY_DIRECTION_LED_COUNT);
            break;
        }
        break;
      }
      else {
        Zone::setLEDs(_joystickLogicalLeds, reactiveColor, JOYSTICK_MAP[i].ledIndices, JOY_DIRECTION_LED_COUNT);
        break;
      }
    }
  }
  showLEDs();
}

/**
 * Directs FastLED to update its controllers with the current LED states.
 * Corrects for color order mismatches
 */
void Player2::showLEDs() {
  memcpy(_joystickOutputLeds, _joystickLogicalLeds, sizeof(_joystickLogicalLeds));

  // The balltop LED uses R,G,B order, unlike the rest of the LEDs in the array, which use G,R,B.
  // Correct for this by swapping R/B before sending the LED state to the controller
  for (int i = 0; i < JOY_BALLTOP_LED_COUNT; i++) {
    uint8_t balltopIndex = JOY_BALLTOP_LEDs[i];
    _joystickOutputLeds[balltopIndex] = CRGB(
      _joystickLogicalLeds[balltopIndex].g,
      _joystickLogicalLeds[balltopIndex].r,
      _joystickLogicalLeds[balltopIndex].b
    );
  }

  FastLED.show();
}