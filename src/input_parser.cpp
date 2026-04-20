#include <input_parser.h>

InputParser::InputParser() : index(0) {}

bool InputParser::parse(Stream &serial, InputPacket &outPacket) {
    while (serial.available()) {
        uint8_t byte = serial.read();

        // --- SYNC ---
        if (index == 0) {
            if (byte != INPUT_HEADER1)
                continue; // wait for header byte
            buffer[index++] = byte;
            continue;
        }

        if (index == 1) {
            if (byte == INPUT_HEADER2) {
                // valid so far, move to next byte
                buffer[index++] = byte;
                continue;
            } else if (byte == INPUT_HEADER1) {
                // stay in sync if this byte could be a header
                buffer[0] = INPUT_HEADER1;
                continue;
            }
            index = 0; // reset if second header byte doesn't match
            continue;
        }

        buffer[index++] = byte;
        
        // --- FULL PACKET ---
        if (index == INPUT_PACKET_SIZE) {
            index = 0; // reset index for next packet

            memcpy(&outPacket, buffer, INPUT_PACKET_SIZE);

            if (validate(outPacket)) {
                return true;  // OK to return, but ONLY if caller loops properly
            } else {
                // stay synced: if this byte could be a header, reuse it
                if (byte == INPUT_HEADER1) {
                    buffer[0] = INPUT_HEADER1;
                    index = 1;
                }
                return false;
            }
        }
    }
    return false; // no complete packet parsed
}

bool InputParser::validate(const InputPacket &packet) {
    return packet.joystick <= MAX_JOYSTICK_VALUE &&
            packet.joystick_mode <= MAX_JOYSTICK_MODE_VALUE &&
            !invalidDirectionCombination(packet.joystick) &&
            crc8((uint8_t*)&packet, INPUT_PACKET_SIZE - 1) == packet.checksum;
}