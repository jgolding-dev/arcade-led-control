#ifndef input_processor_h
#define input_processor_h

#include <input_parser.h>
#include <input_bit_to_led_config.h>

struct ActiveInputLEDs {
    uint8_t buttonIndicies[];
    uint8_t joystickIndicies[];
}

class InputProcessor {
    public:
        InputProcessor();

        void setup();
        void updateP1Packet(InputPacket packet);
        void updateP2Packet(InputPacket packet);
        ActiveInputLEDs getP1ActiveInputs();
        ActiveInputLEDs getP2ActiveInputs();

        InputPacket p1Packet;
        InputPacket lastP1Packet;
        InputPacket p2Packet;
        InputPacket lastP2Packet;

#endif