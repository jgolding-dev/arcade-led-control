#include <input_processor.h>

PlayerInputProcessor::PlayerInputProcessor(InputPacket& packet)
  : InputProcessor() {
    _currentPacket = &packet;
    _lastPacket = &packet;
}

// void PlayerInputProcessor::setup() {
//     for (int i = 0; i < BUTTON_INPUT_COUNT; i++) {
//         _buttonInputs[i] = {BUTTON_MAP[i], false};
//     }
//     for (int i = 0; i < JOYSTICK_INPUT_COUNT; i++) {
//         _joystickInputs[i] = {JOYSTICK_MAP[i], false};
//     }
// }

void PlayerInputProcessor::updatePacket(InputPacket& packet) {
    _lastPacket = _currentPacket;
    _currentPacket = &packet;

    _processInputs();
}

// void PlayerInputProcessor::_processInputs() {
//     uint16_t input16Bit = _currentPacket->buttons_l | (_currentPacket->buttons_h << 8);

//     // Main Button Inputs
//     for (int i = 0; i < BUTTON_INPUT_COUNT; i++) {
//         ActionInputState input = _buttonInputs[i];
//         _lastButtonInputs[i].pressed = input.pressed;
//         _updatePressedState(input, input16Bit);
//     }

//     // Joystick Input
//     for (int i = 0; i < JOYSTICK_INPUT_COUNT; i++) {
//         JoystickInputState input = _joystickInputs[i];
//         _lastJoystickInputs[i].pressed = input.pressed;
//         _updatePressedState(input, _currentPacket->joystick);
//     }
// }

bool PlayerInputProcessor::isButtonActive(uint8_t buttonIndex) {
    uint16_t input16Bit = _currentPacket->buttons_l | (_currentPacket->buttons_h << 8);

    return BUTTON_MAP[buttonIndex].buttonBit && input16Bit;
}

bool PlayerInputProcessor::isJoystickActive(uint8_t buttonIndex) {
    return JOYSTICK_MAP[buttonIndex].buttonBit && _currentPacket->joystick;
}