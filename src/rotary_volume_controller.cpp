#include <rotary_volume_controller.h>

// TinyUSB layout array tracking codes
uint8_t const desc_hid_report[] = {
    TUD_HID_REPORT_DESC_CONSUMER( HID_REPORT_ID(1) )
};

// Bind the HID engine instance explicitly to the consumer descriptor layout 
Adafruit_USBD_HID RotaryVolumeController::_usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_NONE, 2, false);

RotaryVolumeController::RotaryVolumeController(int clkPin, int dtPin, int swPin) {
    _clkPin = clkPin;
    _dtPin = dtPin;
    _swPin = swPin;
    _lastButtonState = HIGH;
    _encoder = RotaryEncoder(clkPin, dtPin, RotaryEncoder::LatchMode::FOUR3);
}

void RotaryVolumeController::setup() {
    _lastPosition = _encoder.getPosition();

    // Start the HID engine
    _usb_hid.begin();
}

/**
 * Updates the state of the encoder
 */
void RotaryVolumeController::tick() {
    _encoder.tick();
}

bool RotaryVolumeController::update() {
    // Ensure the USB client is fully enumerated and active on Windows
    if (!TinyUSBDevice.ready())
        return false;

    bool userInteracted = false;

    long pos = _encoder.getPosition();

    // Track rotations
    if (pos > _lastPosition) {
        userInteracted = true;
        long delta = pos - _lastPosition;
        for (int i = 0; i < delta; i++) {
            // sendReport16 passes the 1-byte Report ID and 2-byte usage code 
            _usb_hid.sendReport16(1, HID_USAGE_CONSUMER_VOLUME_INCREMENT);
            delay(5); // Window processing buffer
            _usb_hid.sendReport16(1, 0); // Release key sequence
        }
    } else if (_lastPosition > pos) {
        userInteracted = true;
        long delta = _lastPosition - pos;
        for (int i = 0; i < delta; i++) {
            _usb_hid.sendReport16(1, HID_USAGE_CONSUMER_VOLUME_DECREMENT);
            delay(5); // Window processing buffer
            _usb_hid.sendReport16(1, 0);
        }
    }
    _lastPosition = pos;

    // Track button press
    bool currentButtonState = digitalRead(_swPin);
    if (currentButtonState == LOW && _lastButtonState == HIGH) {
        userInteracted = true;
        _usb_hid.sendReport16(1, HID_USAGE_CONSUMER_MUTE);
        delay(5); // Window processing buffer
        _usb_hid.sendReport16(1, 0);
    }
    _lastButtonState = currentButtonState;

    return userInteracted;
}

