#pragma once

#include <Arduino.h>
#include <input_protocol.h>
#include <led_layout.h>

struct LedGroup {
    const uint8_t* indices;
    uint8_t count;
};

const uint8_t btn1_leds[] = {0, 1, 2};
const uint8_t btn2_leds[] = {3, 4, 5};

const LedGroup buttonMap[16] = {
    {btn1_leds, 3},
    {btn2_leds, 3}
};