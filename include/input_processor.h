#ifndef input_processor_h
#define input_processor_h

#include <input_parser.h>
#include <input_bit_to_led_config.h>

typedef struct __attribute__ ((__packed__)) {
    ActionInputLEDGroup data;
    bool pressed;
} ActionInputState;

typedef struct __attribute__ ((__packed__)) {
    OptionsInputLEDGroup data;
    bool pressed;
} OptionsInputState;

typedef struct __attribute__ ((__packed__)) {
    JoystickInputLEDGroup data;
    bool pressed;
} JoystickInputState;

class InputProcessor {
    public:
        // Constructor
        InputProcessor();

        // Virtual Destructor
        virtual ~InputProcessor() = default;
        virtual bool isButtonPressed(int buttonIndex){return false;};
        virtual bool isJoystickPressed(int joystickIndex){return false;};

        // virtual functions to be overridden
        virtual void updatePacket(InputPacket& packet){};
        virtual void updatePackets(InputPacket& packet1, InputPacket& packet2){};
        virtual void setup(){};

    protected:
        // virtual functions to be overridden
        virtual void _processInputs(){};

        void _updatePressedState(OptionsInputState &input, uint16_t input16Bit);
        void _updatePressedState(ActionInputState &input, uint16_t input16Bit);
        void _updatePressedState(JoystickInputState &input, uint8_t inputByte);
};

class PlayerInputProcessor : public InputProcessor {
    public:
        // Constructor
        PlayerInputProcessor(InputPacket& packet);

        // Override functions
        void setup();
        void updatePacket(InputPacket& packet);
        bool isButtonPressed(int buttonIndex);
        bool isJoystickPressed(int joystickIndex);
    private:
        // Override functions
        void _processInputs();
        
        ActionInputState _buttonInputs[ACTION_BUTTONS_LED_COUNT];
        JoystickInputState _joystickInputs[JOYSTICK_INPUT_COUNT];
        ActionInputState _lastButtonInputs[ACTION_BUTTONS_LED_COUNT];
        JoystickInputState _lastJoystickInputs[JOYSTICK_INPUT_COUNT];

        InputPacket* _currentPacket;
        InputPacket* _lastPacket;
};

class OptionsInputProcessor : public InputProcessor {
    public:
        // Constructor
        OptionsInputProcessor(InputPacket& p1Packet, InputPacket& p2Packet);

        // Override functions
        void setup();
        void updatePackets(InputPacket &p1Packet, InputPacket &p2Packet);
        bool isButtonPressed(int buttonIndex);
    private:
        // Override functions
        void _processInputs();

        OptionsInputState _optionsInputs[OPTIONS_INPUT_COUNT];
        OptionsInputState _lastOptionsInputs[OPTIONS_INPUT_COUNT];

        InputPacket* _currentP1Packet;
        InputPacket* _currentP2Packet;
        InputPacket* _lastP1Packet;
        InputPacket* _lastP2Packet;
};

#endif