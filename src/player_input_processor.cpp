#include <input_processor.h>

PlayerInputProcessor::PlayerInputProcessor(InputPacket& packet)
  : InputProcessor() {
    _currentPacket = &packet;
    _lastPacket = &packet;
}

void PlayerInputProcessor::updatePacket(InputPacket& packet) {
    _lastPacket = _currentPacket;
    _currentPacket = &packet;
}

bool PlayerInputProcessor::isButtonActive(uint8_t buttonIndex) {
    uint16_t input16Bit = _currentPacket->buttons_l | (_currentPacket->buttons_h << 8);

    return BUTTON_MAP[buttonIndex].buttonBit & input16Bit;
}

bool PlayerInputProcessor::isJoystickActive(uint8_t buttonIndex) {
    return JOYSTICK_MAP[buttonIndex].buttonBit & _currentPacket->joystick;
}