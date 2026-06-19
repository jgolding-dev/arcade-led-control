#include <input_processor.h>

void OptionsInputProcessor::_processInputs() {
    uint16_t input16Bit = _currentPacket->buttons_l | (_currentPacket->buttons_h << 8);

    // Options Button Inputs
    for (int i = 0; i < OPTIONS_INPUT_COUNT; i++) {
        OptionsInputState* input = _optionsInputs[i];
        _lastOptionsInputs[i]->pressed = _optionsInputs[i]->pressed;
        _updatePressedState(input, input16Bit);
    }
}