#include <input_processor.h>

InputProcessor::InputProcessor(){}

void updateP1Packet(InputPacket packet) {
    lastP1Packet = p1Packet;
    p1Packet = packet;
}

void updateP2Packet(InputPacket packet) {
    lastP2Packet = p2Packet;
    p2Packet = packet;
}

ActiveInputLEDs InputProcessor::getP1ActiveInputs() {
    ActiveInputLEDs active;

    uint16_t buttonByte = p1Packet.buttons_l | (p1Packet.buttons_h << 8)
    for(int i = 0; i < 12; i++) {
        uint16_t bit = (1 << i);
        if (buttonByte && bit) {
            active.buttons.add(buttonMap[bit])
        }
    }
}