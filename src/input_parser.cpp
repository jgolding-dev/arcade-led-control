#include "input_parser.h"

InputParser::InputParser() : index(0) {}

bool InputParser::parse(Stream &serial, InputPacket &outPacket) {
    while (serial.available()) {
        uint8_t byte = serial.read();

        // --- SYNC ---
        if (index == 0 && byte != HEADER) {
            continue; // wait for header byte
        }

        buffer[index++] = byte;
        
        // --- FULL PACKET ---
        if (index == sizeof(InputPacket)) {
            index = 0; // reset index for next packet

            memcpy(&outPacket, buffer, sizeof(InputPacket));

            if (validate(outPacket)) {
                return true; // valid packet parsed
            } else {
                // stay synced: if this byte could be a header, reuse it
                if (byte == HEADER) {
                    buffer[0] = HEADER;
                    index = 1;
                }
                return false;
            }
        }
    }
    return false; // no complete packet parsed
}

bool InputParser::validate(const InputPacket &packet) {
    int8_t calc =
        packet.header ^
        packet.buttons_l ^
        packet.buttons_h ^
        packet.joystick ^
        packet.joystick_mode ^
        packet.aux;
        
    return calc == packet.checksum;
}