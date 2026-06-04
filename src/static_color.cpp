#include <animation.h>

void StaticColorAnimation::setup() {
  _colorIndex = 0;
  _isStatic = true;
}

void StaticColorAnimation::apply(CRGB* leds, int count) {
  RGB_t color = COLORS[_colorIndex];
  for (int i = 0; i < count; i++) {
    leds[i].setRGB(color.r, color.g, color.b);
  }
}

void StaticColorAnimation::setModifier(int modifierIndex) {
  _colorIndex = modifierIndex % NUM_COLORS; // Ensure index wraps around
}

void StaticColorAnimation::cycleModifier() {
  _colorIndex = (_colorIndex + 1) % NUM_COLORS;
}