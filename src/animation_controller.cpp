#include <animation_controller.h>

// ---- Enums ---- //
enum LED_ZONE {
  PLAYER_1,
  PLAYER_2,
  OPTIONS,
  ACCENT
};

// ---- Lists ---- //

const int MASTER_BRIGHTNESS_LIST[] = {
  BRIGHTNESS_OFF,
  BRIGHTNESS_LOW,
  BRIGHTNESS_MEDIUM,
  BRIGHTNESS_MAX
};

AnimationController::AnimationController(unsigned long idleTimeoutMs)
  : _idleTimeoutMs(idleTimeoutMs),
    _player1(BRIGHTNESS_MAX),
    _player2(BRIGHTNESS_MAX),
    _options(BRIGHTNESS_MAX),
    _accent(BRIGHTNESS_MAX) {
  
  _zones[PLAYER_1] = &_player1;
  _zones[PLAYER_2] = &_player2;
  _zones[OPTIONS] = &_options;
  _zones[ACCENT] = &_accent;

}


void AnimationController::setup() {
  _currentZone = PLAYER_1;
  _currentBrightness = BRIGHTNESS_MAX;
  _idleStatus = false;
  for (uint8_t i = 0; i < ZONE_COUNT; i++) {
    _zones[i]->setup();
  }
}

void AnimationController::cycleZone() {
  _currentZone = (_currentZone + 1) % ZONE_COUNT;
  _zones[_currentZone]->startZoneSwitchAnimation();
}

void AnimationController::cycleAnimationType() {
  _zones[_currentZone]->cycleAnimationType();
}

/**
 * Cycles the currently selected animation to the the next modifier
 */
void AnimationController::cycleAnimationModifier() {
  _zones[_currentZone]->cycleAnimationModifier();
}

void AnimationController::cycleMasterBrightness() {
  int size = sizeof(MASTER_BRIGHTNESS_LIST) / sizeof(MASTER_BRIGHTNESS_LIST)[0];
  int nextBrightnessIndex = (_currentBrightness + 1) % size;
  int nextBrightness = MASTER_BRIGHTNESS_LIST[nextBrightnessIndex];

  for (uint8_t i = 0; i < ZONE_COUNT; i++) {
    _zones[i]->setMasterBrightness(nextBrightness);
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
    for (uint8_t i = 0; i < ZONE_COUNT; i++) {
      _zones[i]->idle();
    }
  } else {
    for (uint8_t i = 0; i < ZONE_COUNT; i++) {
      _zones[i]->wake();
    }
  }
  _idleStatus = isIdle;
}

/**
 * Advances to the next frame of the currently selected animation for each zone
 */
void AnimationController::processAnimations() {
  for (uint8_t i = 0; i < ZONE_COUNT; i++) {
    _zones[i]->process();
  }
}

/**
 * Resets all animations across all zones to their initial state
 */
void AnimationController::_reset() {
  for (uint8_t i = 0; i < ZONE_COUNT; i++) {
    _zones[i]->reset();
  }
}