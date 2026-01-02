#ifndef animation_controller_h
#define animation_controller_h

#include "Arduino.h"

#include "zones/headers/zone.h"

#include "common/leds.h"
#include "common/brightness_levels.h"

class AnimationController {
    public:
        AnimationController(unsigned long idleTimeoutMs);

        void setup();
        void update();
        void updateAnimationType(int animType);
        void handleIdleState(bool systemActive);
        void cycleZone();
        void cycleAnimationType();
        void cycleAnimationBrightness();
        void cycleAnimationModifier();
        void processAnimations();
        void setIdle(bool isIdle);
    private:
        void _setLEDPinBrightness(int ledPin, int percent);
        void _setAllLEDs(int rValue, int gValue, int bValue);
        void _setColor(uint32_t color);
        void _animateFadeRGB();
        void _reset();
        const unsigned long _idleTimeoutMs;
        int _currentZone;
        int _currentBrightness;
        bool _idleStatus;
};

#endif