#pragma once

#include <Arduino.h>
#include <input_protocol.h>
#include <led_layout.h>


typedef struct __attribute__ ((__packed__)) {
    uint16_t buttonBit;
    const uint8_t* ledIndices[SINGLE_OPTIONS_BTN_LED_COUNT];
} OptionsInputLEDGroup;

typedef struct __attribute__ ((__packed__)) {
    uint16_t buttonBit;
    const uint8_t* ledIndices[ACTION_BTN_LED_COUNT];
} ActionInputLEDGroup;

typedef struct __attribute__ ((__packed__)) {
    uint8_t buttonBit;
    const uint8_t* ledIndices[JOY_DIRECTION_LED_COUNT];
} JoystickInputLEDGroup;

const ActionInputLEDGroup BUTTON_MAP[8] = {
    {B1_BIT, BTN1_LEDs},
    {B2_BIT, BTN2_LEDs},
    {B3_BIT, BTN3_LEDs},
    {B4_BIT, BTN4_LEDs},
    {L1_BIT, L1_LEDs},
    {R1_BIT, R1_LEDs},
    {L2_BIT, L2_LEDs},
    {R2_BIT, R2_LEDs}
};

const OptionsInputLEDGroup OPTIONS_MAP[6] = {
    {EXTRA1_BIT, EXTRA1_LEDs},
    {HOME_BIT, HOME_LEDs},
    {SELECT_BIT, P1_SELECT_LEDs},
    {START_BIT, P1_START_LEDs},
    {SELECT_BIT, P2_SELECT_LEDs},
    {START_BIT, P2_START_LEDs}
};

const JoystickInputLEDGroup JOYSTICK_MAP[4] = {
    {JOY_UP_BIT, JOY_UP_LEDs},
    {JOY_RIGHT_BIT, JOY_RIGHT_LEDs},
    {JOY_DOWN_BIT, JOY_DOWN_LEDs},
    {JOY_LEFT_BIT, JOY_LEFT_LEDs}
};

const int BUTTON_INPUT_COUNT = sizeof(BUTTON_MAP) / sizeof(BUTTON_MAP[0]);
const int OPTIONS_INPUT_COUNT = sizeof(OPTIONS_MAP) / sizeof(OPTIONS_MAP[0]);
const int JOYSTICK_INPUT_COUNT = sizeof(JOYSTICK_MAP) / sizeof(JOYSTICK_MAP[0]);

const int PLAYER2_SELECT_GROUP_INDEX = 4;
const int PLAYER2_START_GROUP_INDEX = 5;