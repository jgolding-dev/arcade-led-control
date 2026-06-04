#include <animation.h>

Animation::Animation() {}

// Default implementations for virtual functions (can be overridden by child classes)
void Animation::setup() {}
void Animation::process() {}
void Animation::cycleModifier() {}
void Animation::setModifier(int modifierIndex) {}
void Animation::reset() {}