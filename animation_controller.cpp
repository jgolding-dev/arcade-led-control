#include "animation_controller.h"

#include <map>
#include <string>

#include "zones/headers/zone.h"
#include "zones/headers/full.h"
#include "zones/headers/player1.h"
#include "zones/headers/player2.h"
#include "zones/headers/options.h"
#include "zones/headers/backlight.h"

#include "common/leds.h"
#include "common/brightness_levels.h"

// ---- Enums ---- //
enum LED_ZONE {
    FULL,
    PLAYER_1,
    PLAYER_2,
    OPTIONS,
    BACKLIGHT
};

// ---- Lists ---- //

const int ANIMATION_BRIGHTNESS_LIST[] = {
    BRIGHTNESS_OFF,
    BRIGHTNESS_LOW,
    BRIGHTNESS_MEDIUM,
    BRIGHTNESS_MAX
};

AnimationController::AnimationController(unsigned long idleTimeoutMs):_idleTimeoutMs(idleTimeoutMs){};

void AnimationController::setup() {
    _initZones();
    _currentZone = OPTIONS,
    // _currentZone = FULL,
    _currentBrightness = BRIGHTNESS_MAX,
    _idleStatus = false;
}

void AnimationController::_initZones() {
    Zone* full = new Full();
    Zone* player1 = new Player1();
    Zone* player2 = new Player2();
    Zone* options = new Options();
    Zone* backlight = new Backlight();
    _ledZones = {
        full,
        player1,
        player2,
        options,
        backlight
    };

    for (int i=0; i < (sizeof(_ledZones) / sizeof(_ledZones[0])); i++) {
        *Zone zone = _ledZones[i];
        zone->setup();
    }
}

void AnimationController::cycleZone() {
    int nextZoneIndex = (_currentZone + 1) % (sizeof(ledZones) / sizeof(ledZones[0])];
    Zone* nextZone = _ledZones[nextZoneIndex];
    nextZone->startCycleAnimation();
    currentZone = nextZoneIndex;
}

void AnimationController::cycleAnimationType() {
    Zone* zone = _ledZones[_currentZone];
    zone->cycleAnimationType();
}

/**
 * Cycles the currently selected animation to the the next modifier
 */
void AnimationController::cycleAnimationModifier() {
    Zone* zone = _ledZones[_currentZone];
    zone->cycleAnimationModifier();
}

// void AnimationController::cycleAnimationBrightness() {
//     int nextBrightnessIndex = (_currentBrightness + 1) % ((sizeof(ANIMATION_BRIGHTNESS_LIST) / sizeof(ANIMATION_BRIGHTNESS_LIST)[0]));
//     _currentBrightness = nextBrightnessIndex;
// }

void AnimationController::handleIdleState(bool systemActive) {
    if (!systemActive && _currentType != IDLE) {
        setIdle(true);
    } else if (systemActive && _currentType == IDLE) {
        setIdle(false);
    }
}

void AnimationController::setIdle(bool isIdle) {
    if (isIdle) {
        for (int i=0; i < (sizeof(_ledZones) / sizeof(_ledZones[0])); i++) {
            _ledZones[i]->idle();
        }
    }
    else {
        for (int i=0; i < (sizeof(_ledZones) / sizeof(_ledZones[0])); i++) {
            _ledZones[i]->wake();
        }
    }
    _idleStatus = isIdle;
}

/**
 * Advances to the next frame of the currently selected animation for each zone
 */
void AnimationController::processAnimations() {
    for (int i=0; i < (sizeof(_ledZones) / sizeof(_ledZones[0])); i++) {
        _ledZones[i]->process();
    }
}

/**
 * Resets all animations across all zones to their initial state
 */
void AnimationController::_reset() {
    for (int i=0; i < (sizeof(_ledZones) / sizeof(_ledZones[0])); i++) {
        _ledZone[i]->reset();
    }
}