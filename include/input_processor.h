#ifndef input_processor_h
#define input_processor_h

#include <input_parser.h>
#include <input_bit_to_led_config.h>

// typedef struct __attribute__ ((__packed__)) {
//     ActionInputLEDGroup data;
//     bool pressed;
// } ActionInputState;

// typedef struct __attribute__ ((__packed__)) {
//     OptionsInputLEDGroup data;
//     bool pressed;
// } OptionsInputState;

// typedef struct __attribute__ ((__packed__)) {
//     JoystickInputLEDGroup data;
//     bool pressed;
// } JoystickInputState;

class InputProcessor {
    public:
        // Constructor
        InputProcessor();

        // Virtual Destructor
        virtual ~InputProcessor() = default;
        virtual bool isButtonActive(uint8_t buttonIndex){return false;};
        virtual bool isJoystickActive(uint8_t joystickIndex){return false;};

        // virtual functions to be overridden
        virtual void updatePacket(InputPacket& packet){};
        virtual void updatePackets(InputPacket& packet1, InputPacket& packet2){};
};

class PlayerInputProcessor : public InputProcessor {
    public:
        // Constructor
        PlayerInputProcessor(InputPacket& packet);

        // Override functions
        void updatePacket(InputPacket& packet);
        bool isButtonActive(uint8_t buttonIndex);
        bool isJoystickActive(uint8_t joystickIndex);
    private:
        InputPacket* _currentPacket;
        InputPacket* _lastPacket;
};

class OptionsInputProcessor : public InputProcessor {
    public:
        // Constructor
        OptionsInputProcessor(InputPacket& p1Packet, InputPacket& p2Packet);

        // Override functions
        void updatePackets(InputPacket &p1Packet, InputPacket &p2Packet);
        bool isButtonActive(uint8_t buttonIndex);
    private:
        InputPacket* _currentP1Packet;
        InputPacket* _currentP2Packet;
        InputPacket* _lastP1Packet;
        InputPacket* _lastP2Packet;
};

#endif