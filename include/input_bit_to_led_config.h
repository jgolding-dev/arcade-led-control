#pragma once

#include <Arduino.h>
#include <input_protocol.h>
#include <led_layout.h>

struct OptionsInputLEDGroup {
    const uint16_t buttonBit;
    const uint8_t* ledIndices[SINGLE_OPTIONS_BTN_LED_COUNT];
};

struct ActionInputLEDGroup {
    const uint16_t buttonBit;
    const uint8_t* ledIndices[ACTION_BTN_LED_COUNT];
};

struct JoystickInputLEDGroup {
    const uint8_t buttonBit;
    const uint8_t* ledIndices[JOY_DIRECTION_LED_COUNT];
};

const ActionInputLEDGroup buttonMap[8] = {
    {B1_BIT, BTN1_LEDs},
    {B2_BIT, BTN2_LEDs},
    {B3_BIT, BTN3_LEDs},
    {B4_BIT, BTN4_LEDs},
    {L1_BIT, L1_LEDs},
    {R1_BIT, R1_LEDs},
    {L2_BIT, L2_LEDs},
    {R2_BIT, R2_LEDs}
};

const OptionsInputLEDGroup optionsMap[6] = {
    {EXTRA1_BIT, EXTRA1_LEDs},
    {HOME_BIT, HOME_LEDs},
    {SELECT_BIT, P1_SELECT_LEDs},
    {START_BIT, P1_START_LEDs},
    {SELECT_BIT, P2_SELECT_LEDs},
    {START_BIT, P2_START_LEDs}
};

const JoystickInputLEDGroup joystickMap[4] = {
    {JOY_UP_BIT, JOY_UP_LEDs},
    {JOY_RIGHT_BIT, JOY_RIGHT_LEDs},
    {JOY_DOWN_BIT, JOY_DOWN_LEDs},
    {JOY_LEFT_BIT, JOY_LEFT_LEDs}
};

const int BUTTON_INPUT_COUNT = sizeof(buttonMap) / sizeof(buttonMap[0]);
const int OPTIONS_INPUT_COUNT = sizeof(optionsMap) / sizeof(optionsMap[0]);
const int JOYSTICK_INPUT_COUNT = sizeof(joystickMap) / sizeof(joystickMap[0]);


const int PLAYER_INPUT_COUNT = BUTTON_INPUT_COUNT + OPTIONS_INPUT_COUNT + JOYSTICK_INPUT_COUNT;