#include <animation_controller.h>

// ---- Enums ---- //
enum LED_ZONE {
  FULL,
  PLAYER_1,
  OPTIONS,
  PLAYER_2,
  ACCENT
};

// ---- Lists ---- //

const int MASTER_BRIGHTNESS_LIST[] = {
  BRIGHTNESS_OFF,
  BRIGHTNESS_LOW,
  BRIGHTNESS_MEDIUM,
  BRIGHTNESS_MAX
};

AnimationController::AnimationController(InputPacket& p1Packet, InputPacket& p2Packet, const unsigned long idleTimeoutMs)
  : _player1Input(p1Packet),
    _player2Input(p2Packet),
    _optionsInput(p1Packet, p2Packet),
    _idleTimeoutMs(idleTimeoutMs),
    _player1(BRIGHTNESS_MAX, _player1Input),
    _player2(BRIGHTNESS_MAX, _player2Input),
    _options(BRIGHTNESS_MAX, _optionsInput),
    _accent(BRIGHTNESS_MAX),
    _full(BRIGHTNESS_MAX, &_player1, &_player2, &_options, &_accent) {
  
  _zones[FULL] = &_full;
  _zones[PLAYER_1] = &_player1;
  _zones[PLAYER_2] = &_player2;
  _zones[OPTIONS] = &_options;
  // _zones[ACCENT] = &_accent;
}

void AnimationController::setup() {
  _currentZone = FULL;
  _currentBrightness = BRIGHTNESS_MAX;
  _zoneSwitchAnimationStartTime = 0;
  _idleStatus = false;
  resetIndicators();

  for (uint8_t i = 0; i < ZONE_COUNT; i++) {
    _zones[i]->setup();
  }

  if (_currentZone == FULL) {
    _zones[FULL]->setAnimationType(_zones[FULL]->currentAnimation);
  }
  else {
    _resumeSubZones();
  }
}

/**
* Sets the brightness value of single LED pin to the specified percentage value
* @param ledPin The pin number of the LED to set the brightness of
* @param percent The brightness percentage value (0-100)
*/
void AnimationController::setLEDPinBrightness(int ledPin, int percent) {
  // Constrain percentage to 0-100
  percent = constrain(percent, 0, 100);

  // set brightness level using gamma correction
  float gamma = 2.2;
  float normalized = percent / 100.0;
  int brightness = pow(normalized, gamma) * 255;
  analogWrite(ledPin, brightness);
}

void AnimationController::cycleZone() {
  if (_zones[_currentZone]->isZoneSwitchActive()) {
    _endZoneSwitch(_currentZone);
    if (_currentZone == FULL) {
      _resumeSubZones();
    }
    _currentZone = (_currentZone + 1) % ZONE_COUNT;
  }
  _zones[_currentZone]->startZoneSwitchAnimation();
  _zoneSwitchAnimationStartTime = millis();
}

void AnimationController::setZone(int zoneIndex) {
  if (_zones[_currentZone]->isZoneSwitchActive()) {
    _endZoneSwitch(_currentZone);
    if (_currentZone == FULL && zoneIndex != FULL) {
      _resumeSubZones();
    }
  }
  _currentZone = zoneIndex;
}

void AnimationController::cycleAnimationType() {
  if (_zones[_currentZone]->isZoneSwitchActive()) {
    _endZoneSwitch(_currentZone);
  }
  _zones[_currentZone]->cycleAnimationType();
}

void AnimationController::setAnimationType(ANIMATION_TYPE animType) {
  if (_zones[_currentZone]->isZoneSwitchActive()) {
    _endZoneSwitch(_currentZone);
  }
  _zones[_currentZone]->setAnimationType(animType);
}

/**
 * Cycles the currently selected animation to the the next modifier
 */
void AnimationController::cycleAnimationModifier() {
  if (_zones[_currentZone]->isZoneSwitchActive()) {
    _endZoneSwitch(_currentZone);
  }
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
  switch (_currentZone) {
    case FULL:
      if (isIdle) {
        _zones[FULL]->idle();
      } else {
        _zones[FULL]->wake();
      }
      break;
    // case CONTROL_PANEL:
    //   if (isIdle) {
    //     _zones[CONTROL_PANEL]->idle();
    //   } else {
    //     _zones[CONTROL_PANEL]->wake();
    //   }
    //   break;
    default:
      if (isIdle) {
        if (_zones[_currentZone]->isZoneSwitchActive()) {
          _endZoneSwitch(_currentZone);
        }
        for (uint8_t i = 0; i < ZONE_COUNT; i++) {
          _zones[i]->idle();
        }
      } else {
        for (uint8_t i = 0; i < ZONE_COUNT; i++) {
          _zones[i]->wake();
        }
      }
      break;
  }
  _idleStatus = isIdle;
}

/**
 * Advances to the next frame of the currently selected animation for each zone
 */
void AnimationController::processAnimations() {
  if (_zones[_currentZone]->isZoneSwitchActive() && (millis() - _zoneSwitchAnimationStartTime) >= ZONE_SWITCH_TIMEOUT_MS) {
    _endZoneSwitch(_currentZone);
  }

  switch (_currentZone) {
    case FULL:
      _zones[FULL]->process();
      break;
    // case CONTROL_PANEL:
    //   _zones[CONTROL_PANEL]->process();
    //   _zones[ACCENT]->process();
    //   break;
    default:
      // Move or copy target zones to a proper subZones array
      for (uint8_t i = FULL + 1; i != FULL; i = (i+1) % ZONE_COUNT) {
        _zones[i]->process();
      }
      break;
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

/**
 * Ends the zone switch animation for the provided zone, and resets timers
 * @param zoneIndex the index of the zone to end the switch animation for
 */
void AnimationController::_endZoneSwitch(int zoneIndex) {
  _zones[zoneIndex]->endZoneSwitchAnimation();
  _zoneSwitchAnimationStartTime = 0;
}

/**
 * Reverts the sub-zones to their previous lighting state after switching back from the full zone
 */
void AnimationController::_resumeSubZones() {
  for (uint8_t i = 0; i < ZONE_COUNT; i++) {
    if (i != FULL) {
      _zones[i]->setAnimationType(_zones[i]->currentAnimation);
    }
  }
} 

/**
 * Resets the joystick mode indicator lights
 */
void AnimationController::resetIndicators() {
  setLEDPinBrightness(P1_DP_MODE_PIN, BRIGHTNESS_OFF);
  setLEDPinBrightness(P1_LS_MODE_PIN, BRIGHTNESS_OFF);
  setLEDPinBrightness(P1_RS_MODE_PIN, BRIGHTNESS_OFF);
  setLEDPinBrightness(P2_DP_MODE_PIN, BRIGHTNESS_OFF);
  setLEDPinBrightness(P2_LS_MODE_PIN, BRIGHTNESS_OFF);
  setLEDPinBrightness(P2_RS_MODE_PIN, BRIGHTNESS_OFF);
}