#include "input_parser.h"

InputParser::InputParser() : index(0) {}

bool InputParser::parse(Stream &serial, InputPacket &outPacket) {
    while (serial.available()) {
        uint8_t byte = serial.read();

        // --- SYNC ---
        if (index == 0) {
            if (byte != HEADER)
                continue; // wait for header byte
            buffer[index++] = byte;
            continue;
        }

        if (index == 1) {
            if (byte == HEADER2) {
                // valid so far, move to next byte
                buffer[index++] = byte;
                continue;
            } else if (byte == HEADER) {
                // stay in sync if this byte could be a header
                buffer[0] = HEADER;
                continue;
            }
            index = 0; // reset if second header byte doesn't match
            continue;
        }

        buffer[index++] = byte;
        
        // --- FULL PACKET ---
        if (index == sizeof(InputPacket)) {
            index = 0; // reset index for next packet

            memcpy(&outPacket, buffer, sizeof(InputPacket));

            if (validate(outPacket)) {
                return true;  // OK to return, but ONLY if caller loops properly
            } else {
                // stay synced: if this byte could be a header, reuse it
                if (byte == HEADER) {
                    buffer[index++] = byte;
                }
                return false;
            }
        }
    }
    return false; // no complete packet parsed
}

bool InputParser::validate(const InputPacket &packet) {
    uint8_t calc =
        packet.header ^
        packet.header2 ^
        packet.buttons_l ^
        packet.buttons_h ^
        packet.joystick ^
        packet.joystick_mode;
        
    return calc == packet.checksum;
}