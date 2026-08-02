#include <input_processor.h>

OptionsInputProcessor::OptionsInputProcessor(InputPacket& p1Packet, InputPacket& p2Packet)
  : InputProcessor(),
    _currentP1Packet(&p1Packet),
    _lastP1Packet(&p1Packet),
    _currentP2Packet(&p2Packet),
    _lastP2Packet(&p2Packet) {}

void OptionsInputProcessor::updatePackets(InputPacket& p1Packet, InputPacket& p2Packet) {
    _lastP1Packet = _currentP1Packet;
    _currentP1Packet = &p1Packet;
    _lastP2Packet = _currentP2Packet;
    _currentP2Packet = &p2Packet;
}

bool OptionsInputProcessor::isButtonActive(uint8_t buttonIndex) {
    if (buttonIndex < 4) { // index 0-3 = player 1 input
        uint16_t p1Input16Bit = _currentP1Packet->buttons_l | (_currentP1Packet->buttons_h << 8);
        return OPTIONS_MAP[buttonIndex].buttonBit & p1Input16Bit;
    }
    else { // index > 3 = player 2 input
        uint16_t p2Input16Bit = _currentP2Packet->buttons_l | (_currentP2Packet->buttons_h << 8);
        return OPTIONS_MAP[buttonIndex].buttonBit & p2Input16Bit;
    }
}