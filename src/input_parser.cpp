#include <input_parser.h>

InputParser::InputParser() {
    reset();
}

void InputParser::reset() {
    state = WAIT_HEADER1;
    index = 0;
    length = 0;
}

bool InputParser::parseByte(uint8_t byte, InputPacket &packet) {
    switch (state) {
        case WAIT_HEADER1:
            if (byte == INPUT_HEADER1) {
                buffer[0] = byte;
                index = 1;
                state = WAIT_HEADER2;
            }
            break;
        case WAIT_HEADER2:
            if (byte == INPUT_HEADER2) {
                buffer[index++] = byte;
                state = WAIT_LENGTH;
            } else if (byte == INPUT_HEADER1) {
                // stay in sync if this byte could be a header
                buffer[0] = INPUT_HEADER1;
                index = 1;
                state = WAIT_HEADER2;
            } else {
               reset(); // invalid second header byte, reset state
            }
            break;
        case WAIT_LENGTH:
            length = byte;

            // safety check
            if (length > MAX_PAYLOAD) {
                reset(); // invalid length, reset
                break;
            }

            buffer[index++] = byte;
            state = READ_PAYLOAD;
            break;
        case READ_PAYLOAD:
            buffer[index++] = byte;
            if (index == (3 + length)) { // header1 + header2 + length + payload (length bytes)
                state = READ_CHECKSUM;
            }
            break;
        case READ_CHECKSUM:
            buffer[index++] = byte; // checksum byte

            // total size = header(2) + length(1) + payload + checksum(1)
            {
                uint8_t totalSize = 2 + 1 + length + 1;

                memcpy(&packet, buffer, totalSize);
                if (validate(packet)) {
                    reset();
                    return true; // valid packet parsed
                } else {
                    // resync: check if this byte could be a header
                    if (byte == INPUT_HEADER1) {
                        buffer[0] = INPUT_HEADER1;
                        index = 1;
                        state = WAIT_HEADER2;
                    } else {
                        reset();
                    }
                }
            }
            break;
        }
    return false; // packet not complete yet
}

/**
 * Validate the parsed packet
 * @param packet The InputPacket to validate
 * @return true if the packet is valid, false otherwise
 */
bool InputParser::validate(const InputPacket &packet) {
    uint8_t calc = crc8((uint8_t*)&packet, INPUT_PACKET_SIZE - 1);

    if (calc != packet.checksum)
        return false; // checksum mismatch

    if (packet.joystick > MAX_JOYSTICK_VALUE || packet.joystick_mode > MAX_JOYSTICK_MODE_VALUE)
        return false; // invalid joystick values
    
    if (invalidDirectionCombination(packet.joystick))
        return false; // invalid joystick direction combination

    return true; // if we made it here, packet is valid
}

/**
 * Calculates CRC-8 checksum using the polynomial 0x07
 * @param data Pointer to the data bytes to calculate the checksum for
 * @param len The number of bytes to include in the checksum calculation
 * @return The calculated CRC-8 checksum byte
 */
uint8_t InputParser::crc8(const uint8_t* data, size_t len) {
    uint8_t crc = 0x00; // Initial value

    for (size_t i = 0; i < len; i++) {
        crc ^= data[i]; // XOR byte into CRC
        for (uint8_t j = 0; j < 8; j++) {
            crc = (crc & 0x80) ? (crc << 1) ^ 0x07 : (crc << 1); // Shift and XOR with polynomial if MSB is set
        }
    }
    return crc;
}

/**
 * Checks for invalid joystick direction combinations (e.g. up + down or left + right)
 * @param joystick The joystick byte to check for invalid combinations
 * @return true if the combination is invalid, false otherwise
 */
bool InputParser::invalidDirectionCombination(uint8_t joystick) {
    // Invalid if both up and down or both left and right are pressed
    return ((joystick & JOY_UP_BIT) && (joystick & JOY_DOWN_BIT)) ||
            ((joystick & JOY_LEFT_BIT) && (joystick & JOY_RIGHT_BIT));
}