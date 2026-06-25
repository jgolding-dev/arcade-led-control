#ifndef animation_controller_h
#define animation_controller_h

#include <brightness_levels.h>
#include <zone.h>
#include <input_protocol.h>
#include <input_processor.h>

const unsigned long ZONE_SWITCH_TIMEOUT_MS = 3UL * 1000UL + 500UL; // 3.5 seconds

class AnimationController {
    public:
        AnimationController(InputPacket &p1Packet,
            InputPacket &p2Packet,
            const unsigned long idleTimeoutMs);

        void setup();
        void handleIdleState(bool systemActive);
        void cycleZone();
        void cycleAnimationType();
        void cycleMasterBrightness();
        void cycleAnimationModifier();
        void setZone(int zoneIndex);
        void setAnimationType(ANIMATION_TYPE animType);
        void setAnimationModifier(int modifierIndex);
        void processAnimations();
        void setIdle(bool isIdle);
        void setLEDPinBrightness(int ledPin, int percent);
        void resetIndicators();
    private:
        void _reset();
        void _resumeSubZones();
        void _endZoneSwitch(int zoneIndex);

        unsigned long _idleTimeoutMs;
        unsigned long _zoneSwitchAnimationStartTime;

        // Zones
        Full _full;
        Player1 _player1;
        Player2 _player2;
        Options _options;
        Accent _accent;

        // Input Processors
        PlayerInputProcessor _player1Input;
        PlayerInputProcessor _player2Input;
        OptionsInputProcessor _optionsInput;

        // Pointer table for iteration
        static constexpr uint8_t ZONE_COUNT = 4;
        Zone* _zones[ZONE_COUNT];

        uint8_t _currentZone;
        uint8_t _currentBrightness;
        bool _idleStatus;
};

#endif