#ifndef input_processor_h
#define input_processor_h

#include <input_parser.h>
#include <input_bit_to_led_config.h>

struct ActionInputState {
    ActionInputLEDGroup data;
    bool pressed;
};

struct OptionsInputState {
    OptionsInputLEDGroup data;
    bool pressed;
};

struct JoystickInputState {
    JoystickInputLEDGroup data;
    bool pressed;
};

class InputProcessor {
    public:
        // Constructor
        InputProcessor();

        // Virtual Destructor
        virtual ~InputProcessor() = default;

        void setup();
        bool isPressed(uint8_t button);
        void updatePacket(InputPacket* packet);

    protected:
        // virtual functions to be overridden
        virtual void _processInputs(){};

        void _updatePressedState(OptionsInputState* input, uint16_t input16Bit);
        void _updatePressedState(ActionInputState* input, uint16_t input16Bit);
        void _updatePressedState(JoystickInputState* input, uint8_t inputByte);

        InputPacket* _currentPacket;
        InputPacket* _lastPacket;
};

class PlayerInputProcessor : public InputProcessor {
    public:
        // Constructor
        PlayerInputProcessor();
    private:
        // Override functions
        void _processInputs();
        
        ActionInputState* _buttonInputs[ACTION_BUTTONS_LED_COUNT];
        JoystickInputState* _joystickInputs[JOYSTICK_INPUT_COUNT];
        ActionInputState* _lastButtonInputs[ACTION_BUTTONS_LED_COUNT];
        JoystickInputState* _lastJoystickInputs[JOYSTICK_INPUT_COUNT];

};

class OptionsInputProcessor : public InputProcessor {
    public:
        // Constructor
        OptionsInputProcessor();
    private:
        // Override functions
        void _processInputs();

        OptionsInputState* _optionsInputs[OPTIONS_INPUT_COUNT];
        OptionsInputState* _lastOptionsInputs[OPTIONS_INPUT_COUNT];
};

#endif