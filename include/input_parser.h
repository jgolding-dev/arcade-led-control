#pragma once
#include <Arduino.h>
#include <input_protocol.h>

class InputParser {
public:
    InputParser();
    
    // feed bytes from UART
    bool parseByte(uint8_t byte, InputPacket &packet);

private:
    enum State {
        WAIT_HEADER1,
        WAIT_HEADER2,
        WAIT_LENGTH,
        READ_PAYLOAD,
        READ_CHECKSUM
    };

    State state;

    uint8_t buffer[32]; // buffer to hold incoming bytes (size should accommodate the largest expected packet)
    uint8_t index;
    uint8_t length;

    void reset();

    bool validate(const InputPacket &packet);
    bool invalidDirectionCombination(uint8_t joystick);
    uint8_t crc8(const uint8_t* data, size_t len);
};