#pragma once

#include <Arduino.h>
#include <input_protocol.h>
#include <led_layout.h>

struct LedGroup {
    const uint16_t buttonBit;
    const uint8_t* ledIndices;
};

const LedGroup buttonMap[12] = {
    {B1_BIT, BTN1_LEDs},
    {B2_BIT, BTN2_LEDs},
    {B3_BIT, BTN3_LEDs},
    {B4_BIT, BTN4_LEDs},
    {L1_BIT, L1_LEDs},
    {R1_BIT, R1_LEDs},
    {L2_BIT, L2_LEDs},
    {R2_BIT, R2_LEDs},
    {SELECT_BIT, P1_SELECT_LEDs},
    {START_BIT, P1_START_LEDs},
    {HOME_BIT, HOME_LEDs},
    {EXTRA1_BIT, EXTRA1_LEDs}
};

const LedGroup joystickMap[4] = {
    {JOY_UP_BIT, JOY_UP_LEDs},
    {JOY_RIGHT_BIT, JOY_RIGHT_LEDs},
    {JOY_DOWN_BIT, JOY_DOWN_LEDs},
    {JOY_LEFT_BIT, JOY_LEFT_LEDs}
};
