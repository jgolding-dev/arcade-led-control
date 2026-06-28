#pragma once

#include <Arduino.h>
#include <input_protocol.h>
#include <led_layout.h>


typedef struct __attribute__ ((__packed__)) {
    uint16_t buttonBit;
    const uint8_t* ledIndices;
} OptionsInputLEDGroup;

typedef struct __attribute__ ((__packed__)) {
    uint16_t buttonBit;
    const uint8_t* ledIndices;
} ActionInputLEDGroup;

typedef struct __attribute__ ((__packed__)) {
    uint8_t buttonBit;
    const uint8_t* ledIndices;
} JoystickInputLEDGroup;

const ActionInputLEDGroup BUTTON_MAP[8] = {
    {B1_BIT, BTN1_LEDs},     // A/X
    {B2_BIT, BTN2_LEDs},     // B/O
    {B3_BIT, BTN3_LEDs},     // X/□
    {B4_BIT, BTN4_LEDs},     // Y/△
    {L1_BIT, L1_LEDs},       // L1/LB
    {R1_BIT, R1_LEDs},       // R1/RB
    {L2_BIT, L2_LEDs},       // L2/LT
    {R2_BIT, R2_LEDs}        // R2/RT
};

enum ActionLEDGroupIndex : uint8_t {
    BUTTON1_INDEX       = 0,     // A/X
    BUTTON2_INDEX       = 1,     // B/O
    BUTTON3_INDEX       = 2,     // X/□
    BUTTON4_INDEX       = 3,     // Y/△
    L1_INDEX            = 4,     // L1/LB
    R1_INDEX            = 5,     // R1/RB
    L2_INDEX            = 6,     // L2/LT
    R2_INDEX            = 7     // R2/RT
};

const OptionsInputLEDGroup OPTIONS_MAP[6] = {
    {EXTRA1_BIT, EXTRA1_LEDs},
    {HOME_BIT, HOME_LEDs},
    {SELECT_BIT, P1_SELECT_LEDs},
    {START_BIT, P1_START_LEDs},
    {SELECT_BIT, P2_SELECT_LEDs},
    {START_BIT, P2_START_LEDs}
};

enum OptionsLEDGroupIndex : uint8_t {
    EXTRA1_INDEX        = 0,
    HOME_INDEX          = 1,
    P1_SELECT_INDEX     = 2,
    P1_START_INDEX      = 3,
    P2_SELECT_INDEX     = 4,
    P2_START_INDEX      = 5
};

const JoystickInputLEDGroup JOYSTICK_MAP[4] = {
    {JOY_UP_BIT, JOY_UP_LEDs},
    {JOY_RIGHT_BIT, JOY_RIGHT_LEDs},
    {JOY_DOWN_BIT, JOY_DOWN_LEDs},
    {JOY_LEFT_BIT, JOY_LEFT_LEDs}
};

enum JoystickLEDGroupIndex : uint8_t {
    JOY_UP_GROUP_INDEX      = 0,
    JOY_RIGHT_GROUP_INDEX   = 1,
    JOY_DOWN_GROUP_INDEX    = 2,
    JOY_LEFT_GROUP_INDEX    = 3
};

const uint8_t BUTTON_INPUT_COUNT = sizeof(BUTTON_MAP) / sizeof(BUTTON_MAP[0]);
const uint8_t OPTIONS_INPUT_COUNT = sizeof(OPTIONS_MAP) / sizeof(OPTIONS_MAP[0]);
const uint8_t JOYSTICK_INPUT_COUNT = sizeof(JOYSTICK_MAP) / sizeof(JOYSTICK_MAP[0]);

const uint8_t PLAYER2_SELECT_GROUP_INDEX = 4;
const uint8_t PLAYER2_START_GROUP_INDEX = 5;