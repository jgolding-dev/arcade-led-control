#ifndef animation_controller_h
#define animation_controller_h

#include <brightness_levels.h>
#include <zone.h>

class AnimationController {
    public:
        AnimationController(unsigned long idleTimeoutMs);

        void setup();
        void update();
        void updateAnimationType(int animType);
        void handleIdleState(bool systemActive);
        void cycleZone();
        void cycleAnimationType();
        void cycleMasterBrightness();
        void cycleAnimationModifier();
        void processAnimations();
        void setIdle(bool isIdle);
    private:
        void _setLEDPinBrightness(int ledPin, int percent);
        void _setAllLEDs(int rValue, int gValue, int bValue);
        void _setColor(uint32_t color);
        void _animateFadeRGB();
        void _reset();

        unsigned long _idleTimeoutMs;

        // Zones
        Full _full;
        Player1 _player1;
        Player2 _player2;
        Options _options;
        Accent _accent;

        // Pointer table for iteration
        static constexpr uint8_t ZONE_COUNT = 4;
        Zone* _zones[ZONE_COUNT];

        uint8_t _currentZone;
        uint8_t _currentBrightness;
        bool _idleStatus;
};

#endif