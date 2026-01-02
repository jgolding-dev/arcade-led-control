#include "animation_controller.h"

// ---- Enums ---- //
enum LED_ZONE {
    FULL,
    PLAYER_1,
    PLAYER_2,
    OPTIONS,
    BACKLIGHT
};

// ---- Lists ---- //

const int MASTER_BRIGHTNESS_LIST[] = {
    BRIGHTNESS_OFF,
    BRIGHTNESS_LOW,
    BRIGHTNESS_MEDIUM,
    BRIGHTNESS_MAX
};

Zone* LED_ZONES[] = {
    new Full(BRIGHTNESS_MAX),
    new Player1(BRIGHTNESS_MAX),
    new Player2(BRIGHTNESS_MAX),
    new Options(BRIGHTNESS_MAX),
    new Backlight(BRIGHTNESS_MAX)
};

AnimationController::AnimationController(unsigned long idleTimeoutMs) : _idleTimeoutMs(idleTimeoutMs) {}

void AnimationController::setup() {
    _currentZone = OPTIONS,
    // _currentZone = FULL,
    _currentBrightness = BRIGHTNESS_MAX;
    _idleStatus = false;

    // Initialize zones
    for (int i=0; i < (sizeof(LED_ZONES) / sizeof(LED_ZONES[0])); i++) {
        Zone* zone = LED_ZONES[i];
        zone->setup();
    }
}

void AnimationController::cycleZone() {
    int nextZoneIndex = (_currentZone + 1) % (sizeof(LED_ZONES) / sizeof(LED_ZONES[0]));
    Zone* nextZone = LED_ZONES[nextZoneIndex];
    nextZone->startCycleAnimation();
    _currentZone = nextZoneIndex;
}

void AnimationController::cycleAnimationType() {
    Zone* zone = LED_ZONES[_currentZone];
    zone->cycleAnimationType();
}

/**
 * Cycles the currently selected animation to the the next modifier
 */
void AnimationController::cycleAnimationModifier() {
    Zone* zone = LED_ZONES[_currentZone];
    zone->cycleAnimationModifier();
}

void AnimationController::cycleAnimationBrightness() {
    int size = sizeof(MASTER_BRIGHTNESS_LIST) / sizeof(MASTER_BRIGHTNESS_LIST)[0];
    int nextBrightnessIndex = (_currentBrightness + 1) % size;
    int nextBrightness = MASTER_BRIGHTNESS_LIST[nextBrightnessIndex];

    for (int i = 0; i < size; i++) {
        LED_ZONES[i]->setMasterBrightness(nextBrightness);
    }
    _currentBrightness = nextBrightness;
}

void AnimationController::handleIdleState(bool systemActive) {
    if (!systemActive && !_idleStatus) {
        setIdle(true);
    } else if (systemActive && _idleStatus) {
        setIdle(false);
    }
}

void AnimationController::setIdle(bool isIdle) {
    if (isIdle) {
        for (int i=0; i < (sizeof(LED_ZONES) / sizeof(LED_ZONES[0])); i++) {
            LED_ZONES[i]->idle();
        }
    }
    else {
        for (int i=0; i < (sizeof(LED_ZONES) / sizeof(LED_ZONES[0])); i++) {
            LED_ZONES[i]->wake();
        }
    }
    _idleStatus = isIdle;
}

/**
 * Advances to the next frame of the currently selected animation for each zone
 */
void AnimationController::processAnimations() {
    for (int i=0; i < (sizeof(LED_ZONES) / sizeof(LED_ZONES[0])); i++) {
        LED_ZONES[i]->process();
    }
}

/**
 * Resets all animations across all zones to their initial state
 */
void AnimationController::_reset() {
    for (int i=0; i < (sizeof(LED_ZONES) / sizeof(LED_ZONES[0])); i++) {
        LED_ZONES[i]->reset();
    }
}