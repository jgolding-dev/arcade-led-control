#pragma once
#include <Arduino.h>

typedef struct {
    uint8_t header;
    uint8_t buttons_l;
    uint8_t buttons_h;
    uint8_t joystick;
    uint8_t joystick_mode;
	uint8_t aux;
    uint8_t checksum;
} __attribute__((packed)) InputPacket;

class InputParser {
public:
    InputParser();
    
    // feed bytes from UART
    bool parse(Stream &serial, InputPacket &outPacket);

private:
    static const uint8_t HEADER = 0xAA;

    uint8_t buffer[sizeof(InputPacket)];
    uint8_t index;

    bool validate(const InputPacket &packet);
};