#ifndef animation_controller_h
#define animation_controller_h

// ---- Pins ----
#define LED_R 16
#define LED_G 18
#define LED_B 20

#include "Arduino.h"

class AnimationController {
    public:
        AnimationController(const int ledPins[], unsigned long idleTimeoutMs, unsigned long fadeStepMs);

        void setup();
        void update();
        void updateAnimationType(int animType);
        void handleIdleState(bool systemActive);
        void cycleAnimationZone();
        void cycleAnimationType();
        void cycleAnimationBrightness();
        void cycleAnimationModifier();
        void processAnimation();
        void setIdle(bool isIdle);
    private:
        const int* _ledPins;
        const unsigned long _idleTimeoutMs;
        unsigned long _fadeStepMs;
        unsigned long _lastAnimStepMs;
        int _currentZone;
        int _cycleAnimationActive;
        int _currentType;
        int _previousType;
        int _currentBrightness;
        int _fadePercent;
        int _fadeDir;
        int _fadeColorIndex;
        int _staticColorIndex;
        void _setBrightness(int ledPin, int percent);
        void _setAllLEDs(int rValue, int gValue, int bValue);
        void _setColor(uint32_t color);
        void _animateFadeRGB();
        void _reset();
};

#endif