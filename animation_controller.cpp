#include "animation_controller.h"
#include <map>

const int BRIGHTNESS_OFF = 0;
const int BRIGHTNESS_LOW = 33;
const int BRIGHTNESS_MEDIUM = 66;
const int BRIGHTNESS_MAX = 100;

// ---- Animation Enums ---- //
enum ANIMATION_ZONE {
    ALL,
    PLAYER_1,
    PLAYER_2,
    OPTIONS,
    BACKLIGHT
};

enum ANIMATION_TYPE {
    STATIC,
    COLOR_SHIFT,
    RAINBOW,
    FADE,
    PULSE,
    IDLE
};

// ---- Animation Lists ---- //
const ANIMATION_ZONE ANIMATION_ZONE_LIST[] = {
    ALL,
    PLAYER_1,
    PLAYER_2,
    OPTIONS,
    BACKLIGHT
};
const ANIMATION_TYPE ANIMATION_TYPE_LIST[] = {    
    STATIC,
    COLOR_SHIFT,
    RAINBOW,
    FADE,
    PULSE,
    IDLE
};
const int ANIMATION_BRIGHTNESS_LIST[] = {
    BRIGHTNESS_OFF,
    BRIGHTNESS_LOW,
    BRIGHTNESS_MEDIUM,
    BRIGHTNESS_MAX
};
const uint32_t STATIC_COLOR_LIST[] = {
    0x0000FF, // Blue
    0xFF0000, // Red
    0x00FF00, // Green
    0xFFFFFF, // White
    0xFFFF00, // Yellow
    0xFF00FF, // Magenta
    0x00FFFF  // Cyan
};

AnimationController::AnimationController(const int ledPins[], unsigned long idleTimeoutMs, unsigned long fadeStepMs):
        _ledPins(ledPins),
        _idleTimeoutMs(idleTimeoutMs),
        _fadeStepMs(fadeStepMs),
        _currentType(STATIC),
        _previousType(IDLE),
        _currentZone(ALL),
        _cycleAnimationActive(false),
        _currentBrightness(BRIGHTNESS_MAX),
        _staticColorIndex(0) {
    _setAllLEDs(0, 0, 0);
    _reset();
}

/**
* Updates the currently selected animation, and tracks the previous set animation.
* @param anim The animation to set.
*/
void updateAnimationType(ANIMATION_TYPE animType) {
    _previousType = _currentType;
    _currentType = animType;
    _reset();
    switch (animType) {
        case STATIC:
            _setColor(STATIC_COLOR_LIST[_staticColorIndex]);
            break;
        case IDLE:
            _setAllLEDs(0, 0, 0);
            break;
        default:
            break;
    }
}

void cycleAnimationZone(ANIMATION_ZONE zone) {
    ANIMATION_ZONE nextZone = ANIMATION_ZONE_LIST[(_currentZone + 1) % ANIMATION_ZONE_LIST.size());
    _cycleAnimationActive = true;                                       
}

void cycleAnimationType() {
    ANIMATION_TYPE nextType = ANIMATION_TYPE_LIST[(_currentType + 1) % ANIMATION_TYPE_LIST.size()];
    updateAnimationType(nextType);
}

void cycleAnimationBrightness() {
    int nextBrightnessIndex = (_currentBrightnessIndex + 1) % ANIMATION_BRIGHTNESS_LIST.size();
    _previousBrightnessIndex = _currentBrightnessIndex;
    _currentBrightnessIndex = nextBrightnessIndex;
}

void handleIdleState(bool systemActive) {
    if (!systemActive && _currentType != IDLE) {
        updateAnimationType(IDLE);
    } else if (systemActive && _currentType == IDLE) {
        updateAnimationType(_previousType);
    }
}

/**
 * Advances to the next frame of the current animation
 */
void processAnimation() {
    unsigned long now = millis();
    if (now - _lastAnimStepMs < _fadeStepMs) {
        return;
    }
    _lastAnimStepMs = now;

    switch (ANIMATION_TYPE_LIST[_currentType]) {
        case COLOR_SHIFT:
            // To be implemented
        case RAINBOW:
            // To be implemented
            break;
        case FADE:
            animateFadeRGB();
            break;
        case PULSE:
            // To be implemented
            break;
        default:
            // No animation
            break;
    }
}

/**
* Fades each color (R/G/B) in and out, sequentially
*/
void _animateFadeRGB() {
  // Turn off all LEDs first
  _setAllLEDs(0, 0, 0);

  int pin = _ledPins[fadeColorIndex];

  // Calculate brightness as a percentage of the current brightness setting
  float normalized = fadePercent / 100.0;
  int brightness = normalized * ANIMATION_BRIGHTNESS_LIST[_currentBrightnessIndex];
  _setBrightness(pin, brightness);

  fadePercent += fadeDir;

  if (fadePercent >= 100) {
    fadeDir = -1;
  }
  else if (fadePercent <= 0) {
    fadeDir = 1;
    fadeColorIndex = (fadeColorIndex + 1) % _ledPins.size();
  }
}

/**
 * Cycles the currently selected animation to the the next modifier
 */
void cycleAnimationModifier() {
    int nextColorIndex;
    switch (ANIMATION_TYPE_LIST[_currentType]) {
        case STATIC:
            nextColorIndex = (_staticColorIndex + 1) % (sizeof(STATIC_COLOR_LIST) / sizeof(STATIC_COLOR_LIST[0]));
            _setColor(STATIC_COLOR_LIST[nextColorIndex]);
            _staticColorIndex = nextColorIndex;
            break;
        default:
            // No modifier
            break;
    }
}

/**
 * Sets LEDs to the specified hex color value
 * @param color the hex color value to set the LEDs to
 */
void _setColor(uint32_t color) {
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;
    _setAllLEDs(r, g, b);
}

/**
* Sets the LED brightness to the specified percentage value
* @param ledPin The pin number of the LED to set the brightness of
* @param percent The brightness percentage value (0-100)
*/
void _setBrightness(int ledPin, int percent) {
    // Constrain percentage to 0-100
    percent = constrain(percent, 0, 100);

    // set brightness level using gamma correction
    float gamma = 2.2;
    float normalized = percent / 100.0;
    int brightness = pow(normalized, gamma) * 255;
    analogWrite(ledPin, brightness);
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param rValue the brightness value of the red channel
* @param gValue the brightness value of the green channel
* @param bValue the brightness value of the blue channel
*/
void _setAllLEDs(int rValue, int gValue, int bValue) {
  _setBrightness(LED_R, rValue);
  _setBrightness(LED_G, gValue);
  _setBrightness(LED_B, bValue);
}

/**
 * Resets all animations to their initial state
 */
void _reset() {
    _lastAnimStepMs = 0;
    _fadePercent = 0;
    _fadeDir = 1;
    _fadeColorIndex = 0;
}