#ifndef rotary_volume_controller_h
#define rotary_volume_controller_h

#include <Arduino.h>
#include <Adafruit_TinyUSB.h> 
#include <RotaryEncoder.h>

class RotaryVolumeController {
    public:
        RotaryVolumeController(int clkPin, int dtPin, int swPin);

        void setup();
        void tick();
        bool update(); // Returns true if user actively changed volume/mute.

        // Static ISR function wrapper because standard C++ class methods cannot be attached directly to interrupts
        static void __not_in_flash_func(handleInterrupt)();

    private:
        int _clkPin;
        int _dtPin;
        int _swPin;
        
        long _lastPosition;
        bool _lastButtonState;

        RotaryEncoder _encoder;

        static Adafruit_USBD_HID _usb_hid;
};

#endif