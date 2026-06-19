#include <input_processor.h>

void PlayerInputProcessor::_processInputs() {
    uint16_t input16Bit = _currentPacket->buttons_l | (_currentPacket->buttons_h << 8);

    // Main Button Inputs
    for (int i = 0; i < BUTTON_INPUT_COUNT; i++) {
        ActionInputState* input = _buttonInputs[i];
        _lastButtonInputs[i]->pressed = input->pressed;
        _updatePressedState(input, input16Bit);
    }

    // Joystick Input
    for (int i = 0; i < JOYSTICK_INPUT_COUNT; i++) {
        JoystickInputState* input = _joystickInputs[i];
        _lastJoystickInputs[i]->pressed = input->pressed;
        _updatePressedState(input, _currentPacket->joystick);
    }
}