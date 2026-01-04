#include "animation_controller.h"
#include <vector>
#include <memory>  // Required for smart pointers

// ---- Enums ---- //
enum LED_ZONE {
  // FULL,
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

std::vector<Zone*> LED_ZONES;

AnimationController::AnimationController(unsigned long idleTimeoutMs)
  : _idleTimeoutMs(idleTimeoutMs) {}

void AnimationController::setup() {
  _currentZone = PLAYER_1;
  // _currentZone = FULL,
  _currentBrightness = BRIGHTNESS_MAX;
  _idleStatus = false;

  // Initialize zones
  LED_ZONES = {
    // new Full(BRIGHTNESS_MAX),
    new Player1(BRIGHTNESS_MAX),
    new Player2(BRIGHTNESS_MAX),
    new Options(BRIGHTNESS_MAX),
    new Backlight(BRIGHTNESS_MAX)
  };
  for (const auto& zone : LED_ZONES) {
    zone->setup();
  }
}

void AnimationController::cycleZone() {
  int nextZoneIndex = (_currentZone + 1) % LED_ZONES.size();
  LED_ZONES[nextZoneIndex]->cycleAnimationType();
  _currentZone = nextZoneIndex;
}

void AnimationController::cycleAnimationType() {
  LED_ZONES[_currentZone]->cycleAnimationType();
}

/**
 * Cycles the currently selected animation to the the next modifier
 */
void AnimationController::cycleAnimationModifier() {
  LED_ZONES[_currentZone]->cycleAnimationModifier();
}

void AnimationController::cycleAnimationBrightness() {
  int size = sizeof(MASTER_BRIGHTNESS_LIST) / sizeof(MASTER_BRIGHTNESS_LIST)[0];
  int nextBrightnessIndex = (_currentBrightness + 1) % size;
  int nextBrightness = MASTER_BRIGHTNESS_LIST[nextBrightnessIndex];

  for (const auto& zone : LED_ZONES) {
    zone->setMasterBrightness(nextBrightness);
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
    for (const auto& zone : LED_ZONES) {
      zone->idle();
    }
  } else {
    for (const auto& zone : LED_ZONES) {
      zone->wake();
    }
  }
  _idleStatus = isIdle;
}

/**
 * Advances to the next frame of the currently selected animation for each zone
 */
void AnimationController::processAnimations() {
  for (const auto& zone : LED_ZONES) {
    zone->process();
  }
}

/**
 * Resets all animations across all zones to their initial state
 */
void AnimationController::_reset() {
  for (const auto& zone : LED_ZONES) {
    zone->reset();
  }
}