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
  currentAnimation = CUSTOM;
}

/**
* Sets the brightness level (%) of all LED channels (R/G/B)
* @param rValue the brightness value of the red channel
* @param gValue the brightness value of the green channel
* @param bValue the brightness value of the blue channel
*/
void Full::setAllZone(uint8_t rValue, uint8_t gValue, uint8_t bValue) {
  for(uint8_t i = 0; i < ZONE_COUNT; i++) {
    _subZones[i]->setAllZone(rValue, gValue, bValue);
  }
}

/**
 * Applies the custom lighting pattern to the zone based on the specified custom type
 * @param type the custom type to apply
 */
void Full::applyCustom(const CustomType &type) {
  for(uint8_t i = 0; i < ZONE_COUNT; i++) {
    _subZones[i]->applyCustom(type);
  }
}