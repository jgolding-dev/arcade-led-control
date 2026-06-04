#ifndef animation_h
#define animation_h

#include <Arduino.h>
#include <fastled_config.h>
#include <led_layout.h>
#include <input_protocol.h>
#include <input_bit_to_led_config.h>

class Animation {
    public:
        // Constructor
        Animation();

        // Virtual Destructor
        virtual ~Animation() = default;

        // Virtual to be overriden by children
        virtual void setup();
        virtual void process(CRGB* leds, int count);
        virtual void cycleModifier();
        virtual void setModifier(int modifierIndex);
        virtual void getModifierIndex();
        virtual void reset();
        virtual bool isStatic() { return _isStatic; };
        virtual void apply(CRGB* leds, int count) {};
    protected:
        bool _isStatic;
};

class StaticColorAnimation : public Animation {
    public:
        // Constructor
        StaticColorAnimation::StaticColorAnimation();

        // Override Functions
        void setup() override;
        void apply(CRGB* leds, int count) override;
        void setModifier(int modifierIndex) override;
        void cycleModifier() override;
    private:
        int _colorIndex;
};

class FadeAnimation : public Animation {
    public:
        // Constructor
        FadeAnimation();

        // Override Functions
        void setup() override;
        void process(CRGB* leds, int count) override;
        void setModifier(int modifierIndex) override;
        void cycleModifier() override;
    private:
        int _fadeStepIndex;
};

class CustomAnimation : public Animation {
    public:
        // Constructor
        CustomAnimation();

        // Override Functions
        void setup() override;
        void process(CRGB* leds, int count) override;
    private:
        int _customTypeIndex;
};

#endif