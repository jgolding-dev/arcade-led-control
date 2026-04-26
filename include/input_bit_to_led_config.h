#pragma once

#include <Arduino.h>
#include <input_protocol.h>
#include <led_layout.h>

struct LedGroup {
    const uint8_t* indices;
    uint8_t count;
};

// ----------------- Buttons ----------------- //
const uint8_t BTN1_LEDs[] = {B1_LED, B1_LED + 1};
const uint8_t BTN2_LEDs[] = {B2_LED, B2_LED + 1};
const uint8_t BTN3_LEDs[] = {B3_LED, B3_LED + 1};
const uint8_t BTN4_LEDs[] = {B4_LED, B4_LED + 1};
const uint8_t L1_LEDs[] = {L1_LED, L1_LED + 1};
const uint8_t R1_LEDs[] = {R1_LED, R1_LED + 1};
const uint8_t L2_LEDs[] = {L2_LED, L2_LED + 1};
const uint8_t R2_LEDs[] = {R2_LED, R2_LED + 1};
const uint8_t P1_SELECT_LEDs[] = {P1_SELECT_LED};
const uint8_t P1_START_LEDs[] = {P1_START_LED};
const uint8_t P2_SELECT_LEDs[] = {P2_SELECT_LED};
const uint8_t P2_START_LEDs[] = {P2_START_LED};
const uint8_t HOME_LEDs[] = {HOME_LED};
const uint8_t EXTRA1_LEDs[] = {EXTRA1_BIT};
const uint8_t EXTRA2_LEDs[] = {EXTRA2_BIT};

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
    {EXTRA1_LEDs, 1},
    {EXTRA2_LEDs, 1},
};

// ----------------- Joystick ----------------- //
const uint8_t JOY_UP_LEDs[] = {JOY_UP_LED};
const uint8_t JOY_UP_RIGHT_LEDs[] = {JOY_UP_RIGHT_LED};
const uint8_t JOY_RIGHT_LEDs[] = {JOY_RIGHT_LED};
const uint8_t JOY_DOWN_RIGHT_LEDs[] = {JOY_DOWN_RIGHT_LED};
const uint8_t JOY_DOWN_LEDs[] = {JOY_DOWN_LED};
const uint8_t JOY_DOWN_LEFT_LEDs[] = {JOY_DOWN_LEFT_LED};
const uint8_t JOY_LEFT_LEDs[] = {JOY_LEFT_LED};
const uint8_t JOY_UP_LEFT_LEDs[] = {JOY_UP_LEFT_LED};
const uint8_t JOY_BALLTOP_LEDs[] = {JOY_BALLTOP_LED};

const LedGroup joystickMap[9] = {
    {JOY_UP_LEDs, 1},
    {JOY_UP_RIGHT_LEDs, 1},
    {JOY_RIGHT_LEDs, 1},
    {JOY_DOWN_RIGHT_LEDs, 1},
    {JOY_DOWN_LEDs, 1},
    {JOY_DOWN_LEFT_LEDs, 1},
    {JOY_LEFT_LEDs, 1},
    {JOY_UP_LEFT_LEDs, 1},
    {JOY_BALLTOP_LEDs, 1}
};
