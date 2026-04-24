#include <input_parser.h>

const bool DEBUG_MODE = false;

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
                if (DEBUG_MODE) Serial.println("Received header1 at index 0. New state:");
                buffer[0] = byte;
                index = 1;
                state = WAIT_HEADER2;
                if (DEBUG_MODE) printState();
            }
            break;
        case WAIT_HEADER2:
            if (byte == INPUT_HEADER2) {
                if (DEBUG_MODE) Serial.println("Received header2 at index 1. New state:");
                buffer[index++] = byte;
                state = WAIT_LENGTH;
                if (DEBUG_MODE) printState();
            } else if (byte == INPUT_HEADER1) {
                // stay in sync if this byte could be a header
                if (DEBUG_MODE) Serial.println("Received header1 at index 1. New state:");
                buffer[0] = INPUT_HEADER1;
                index = 1;
                state = WAIT_HEADER2;
                if (DEBUG_MODE) printState();
            } else {
                if (DEBUG_MODE) Serial.println("Invalid header2 byte at index 1. Resetting state.");
                reset(); // invalid second header byte, reset state
                if (DEBUG_MODE) printState();
            }
            break;
        case WAIT_LENGTH:
            if (DEBUG_MODE) Serial.print("Received length byte " + String(byte) + " at index 2. ");
            length = byte;

            // safety check
            if (length != INPUT_PACKET_SIZE - 4) { // Sould be payload size: packet size - header(2) - length(1) - checksum(1)
                if (DEBUG_MODE) Serial.println("Invalid. Resetting state:");
                reset(); // invalid length, reset
                if (DEBUG_MODE) printState();
                break;
            }

            buffer[index++] = byte;
            state = READ_PAYLOAD;
            if (DEBUG_MODE) Serial.println("New state:");
            if (DEBUG_MODE) printState();
            break;
        case READ_PAYLOAD:
            if (DEBUG_MODE) Serial.println("Received payload byte at index " + String(index) + ". New state:");
            buffer[index++] = byte;
            if (index == (3 + length)) { // header1 + header2 + length + payload (length bytes)
                state = READ_CHECKSUM;
            }
            if (DEBUG_MODE) printState();
            break;
        case READ_CHECKSUM:
            if (DEBUG_MODE) Serial.println("Received checksum byte at index " + String(index) + ". Attempting to validate packet...");
            buffer[index++] = byte; // checksum byte

            // total size = header(2) + length(1) + payload + checksum(1)
            {
                uint8_t totalSize = 2 + 1 + length + 1;

                memcpy(&packet, buffer, totalSize);
                if (validate(packet)) {
                    if (DEBUG_MODE) Serial.println("Packet validated successfully. Resetting state for next packet.");
                    reset();
                    if (DEBUG_MODE) printState();
                    return true; // valid packet parsed
                } else {
                    // resync: check if this byte could be a header
                    if (byte == INPUT_HEADER1) {
                        if (DEBUG_MODE) Serial.println("Invalid packet, but received header1. New state:");
                        buffer[0] = INPUT_HEADER1;
                        index = 1;
                        state = WAIT_HEADER2;
                        if (DEBUG_MODE) printState();
                    } else {
                        if (DEBUG_MODE) Serial.println("Invalid packet and no header detected. Resetting state.");
                        reset();
                        if (DEBUG_MODE) printState();
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
    
    // if (invalidDirectionCombination(packet.joystick))
    //     return false; // invalid joystick direction combination

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

void InputParser::printState() {
    Serial.println("-------------------------------");
    Serial.print("Current state: ");
    switch (state) {
        case WAIT_HEADER1: Serial.println("WAIT_HEADER1"); break;
        case WAIT_HEADER2: Serial.println("WAIT_HEADER2"); break;
        case WAIT_LENGTH: Serial.println("WAIT_LENGTH"); break;
        case READ_PAYLOAD: Serial.println("READ_PAYLOAD"); break;
        case READ_CHECKSUM: Serial.println("READ_CHECKSUM"); break;
    }
    Serial.print("Buffer index: "); Serial.println(index);
    Serial.print("Buffer length: "); Serial.println(length);
    Serial.println("-------------------------------");
    Serial.println();
}