#ifndef animation_controller_h
#define animation_controller_h

// ---- Pins ----
#define LED_R 16
#define LED_G 18
#define LED_B 20

#include "Arduino.h"
#include "zones/headers/zone.h"

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
        const int* _ledPins;
        const Zone* _ledZones;
        const unsigned long _idleTimeoutMs;
        unsigned long _fadeStepMs;
        unsigned long _lastAnimStepMs;
        int _currentZone;
        int _currentType;
        int _previousType;
        int _currentBrightness;
        bool _idleStatus;
        void _setBrightness(int ledPin, int percent);
        void _setAllLEDs(int rValue, int gValue, int bValue);
        void _setColor(uint32_t color);
        void _animateFadeRGB();
        void _reset();
};

#endif