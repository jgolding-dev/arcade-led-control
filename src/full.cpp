#include <zone.h>

Full::Full(int brightness, Player1* p1Zone, Player2* p2Zone, Options* opZone, Accent* accZone)
  : Zone(brightness) {
    _player1Zone = p1Zone;
    _player2Zone = p2Zone;
    _optionsZone = opZone;
    _accentZone = accZone;

    _subZones[0] = _player1Zone;
    _subZones[1] = _player2Zone;
    _subZones[2] = _optionsZone;
    _subZones[3] = _accentZone;
  }

void Full::setup() {
  animationTypes = FULL_ANIMATION_TYPES;
  previousAnimation = STATIC;
  currentAnimation = IDLE;
  _staticColorIndex = 0;
  _fadeStepIndex = 1;  // FADE_STEP_NORMAL
  _fadeColorIndex = 0;
}

void Full::setAnimationType(ANIMATION_TYPE animType) {
  previousAnimation = currentAnimation;
  currentAnimation = animType;
  reset();
  for (uint8_t i = 0; i < ZONE_COUNT; i++) {
    _subZones[i]->reset();
  }
  setAllLEDs(0, 0, 0);

  int animationModifier = -1;
  switch (currentAnimation) {
    case STATIC:
      animationModifier = _staticColorIndex;
    case FADE:
      animationModifier = _fadeStepIndex;
    default:
      // No modifier for the currently selected animation
      break;
  }

  for(uint8_t i = 0; i < ZONE_COUNT; i++) {
    _subZones[i]->setAnimationType(animType);
    if (animationModifier >= 0) {
      _subZones[i]->setAnimationModifier(animationModifier);
    }
  }
}

/**
 * Advances to the next frame of the current animation
 */
void Full::process() {
  for (uint8_t i = 0; i < ZONE_COUNT; i++) {
    _subZones[i]->process();
  }
}

/**
 * Cycles the currently selected animation to the the next modifier
 */
void Full::cycleAnimationModifier() {
  int animationModifier = -1;
  switch (currentAnimation) {
    case STATIC:
      _staticColorIndex = (_staticColorIndex + 1) % (sizeof(STATIC_COLORS) / sizeof(STATIC_COLORS[0]));
      animationModifier = _staticColorIndex;
    case FADE:
      _fadeStepIndex = (_fadeStepIndex + 1) % (sizeof(FADE_STEP_MS) / sizeof(FADE_STEP_MS[0]));
      animationModifier = _fadeStepIndex;
    default:
      // No modifier for the currently selected animation
      break;
  }

  if (animationModifier >= 0) {
    for(uint8_t i = 0; i < ZONE_COUNT; i++) {
      _subZones[i]->setAnimationModifier(animationModifier);
    }
  }
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param rValue the brightness value of the red channel
* @param gValue the brightness value of the green channel
* @param bValue the brightness value of the blue channel
*/
void Full::setAllLEDs(int rValue, int gValue, int bValue) {
  for(uint8_t i = 0; i < ZONE_COUNT; i++) {
    _subZones[i]->setAllLEDs(rValue, gValue, bValue);
  }
}