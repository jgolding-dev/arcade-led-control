#pragma once

#include <Arduino.h>
#include <input_protocol.h>
#include <led_layout.h>

struct LedGroup {
    const uint8_t* indices;
    uint8_t count;
};

const LedGroup buttonMap[15] = {
    {BTN1_LEDs, 2},
    {BTN2_LEDs, 2},
    {BTN3_LEDs, 2},
    {BTN4_LEDs, 2},
    {L1_LEDs, 2},
    {R1_LEDs, 2},
    {L2_LEDs, 2},
    {R2_LEDs, 2},
    {P1_SELECT_LEDs, 1},
    {P1_START_LEDs, 1},
    {P2_SELECT_LEDs, 1},
    {P2_START_LEDs, 1},
    {HOME_LEDs, 1},
    {EXTRA1_LEDs, 1}
};

const LedGroup joystickMap[9] = {
    {JOY_UP_LEDs, 4},
    {JOY_UP_RIGHT_LEDs, 4},
    {JOY_RIGHT_LEDs, 4},
    {JOY_DOWN_RIGHT_LEDs, 4},
    {JOY_DOWN_LEDs, 4},
    {JOY_DOWN_LEFT_LEDs, 4},
    {JOY_LEFT_LEDs, 4},
    {JOY_UP_LEFT_LEDs, 4},
    {JOY_BALLTOP_LEDs, 1}
};
