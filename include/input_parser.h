#pragma once
#include <Arduino.h>
#include <input_protocol.h>

uint8_t crc8(const uint8_t* data, size_t len) {
    uint8_t crc = 0x00; // Initial value
    for (size_t i = 0; i < len; i++) {
        crc ^= data[i]; // XOR byte into CRC
        for (uint8_t j = 0; j < 8; j++) {
            crc = (crc & 0x80) ? (crc << 1) ^ 0x07 : (crc << 1); // Shift and XOR with polynomial if MSB is set
        }
    }
    return crc;
}

class InputParser {
public:
    InputParser();
    
    // feed bytes from UART
    bool parse(Stream &serial, InputPacket &outPacket);

private:
    uint8_t buffer[sizeof(InputPacket)];
    uint8_t index;

    bool validate(const InputPacket &packet);
    bool invalidDirectionCombination(uint8_t joystick) {
        // Invalid if both up and down or both left and right are pressed
        return ((joystick & JOY_UP_BIT) && (joystick & JOY_DOWN_BIT)) ||
               ((joystick & JOY_LEFT_BIT) && (joystick & JOY_RIGHT_BIT));
    }
};