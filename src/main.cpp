#include <Arduino.h>
#include <pins.h>
#include <led_layout.h>
#include <animation_controller.h>

const bool DEBUG_MODE = false;

// ---- Timing ----
const unsigned long IDLE_TIMEOUT_MS = 15UL * 60UL * 1000UL;  // 15 Minutes

// For Testing
const unsigned long CYCLE_MOD_MS = 5UL * 1000UL;    // 5 Seconds
const unsigned long CYCLE_TYPE_MS = 35UL * 1000UL;  // 35 Seconds
const unsigned long CYCLE_ZONE_MS = 35UL * 1000UL;  // 35 Seconds

//

// ---- Pin States ----
PinStatus lastActPinState    = LOW;
PinStatus lastMacro1PinState = LOW;
PinStatus lastMacro2PinState = LOW;
PinStatus lastMacro3PinState = LOW;
PinStatus lastMacro4PinState = LOW;

unsigned long lastActivityMs = 0;
unsigned long lastTypeSwitch = 0;
unsigned long lastModSwitch  = 0;
unsigned long lastZoneSwitch = 0;

bool systemActive = true;

AnimationController animController(IDLE_TIMEOUT_MS);


// local function declarations
void handleActivity();
void handleMacroEvent();
void updateActivityState(bool active);

void setup() {
  delay(100); // allow USB stack to settle

  if (DEBUG_MODE) {
    Serial.begin(9600);
  }
  // Initialize I/O
  Pins::initPins();

  // Set last activity time and update state
  lastActivityMs = 0;
  lastTypeSwitch = 0;
  lastModSwitch  = 0;
  lastZoneSwitch = 0;
  systemActive = true;

  animController.setup();
}

void loop() {
  handleActivity();
  animController.handleIdleState(systemActive);
  handleMacroEvent();
  if (DEBUG_MODE) {
    if ((millis() - lastZoneSwitch) > CYCLE_ZONE_MS) {
      Serial.println("Cycling Zone...");
      delay(50);
      animController.cycleZone();
      lastZoneSwitch = millis();
      lastModSwitch = millis();
    }
    else if ((millis() - lastModSwitch) > CYCLE_MOD_MS) {
      Serial.println("Cycling Modifier...");
      delay(50);
      animController.cycleAnimationModifier();
      lastModSwitch = millis();
    }
  }
  animController.processAnimations();
}

/**
* Updates the activity state of the LED controller. If active, refresh the
* time of last activity.
* @param active The activity state to update to.
*/
void updateActivityState(bool active) {
  if (active) {
    lastActivityMs = millis();
    systemActive = true;
  } else {
    systemActive = false;
  }
}

/**
* Updates the system activity state based on the recorded activity input state
*/
void handleActivity() {
  PinStatus current = digitalRead(ACTIVITY_PIN);

  if (current == HIGH && lastActPinState == LOW) {
    updateActivityState(true);
  } else if (systemActive && (millis() - lastActivityMs) > IDLE_TIMEOUT_MS) {
    updateActivityState(false);
  }

  lastActPinState = current;
}

/**
* Sets the animation state based on the triggered activity event
*/
void handleMacroEvent() {
  PinStatus currentMacro1 = digitalRead(MACRO_1_PIN);
  PinStatus currentMacro2 = digitalRead(MACRO_2_PIN);
  PinStatus currentMacro3 = digitalRead(MACRO_3_PIN);
  PinStatus currentMacro4 = digitalRead(MACRO_4_PIN);

  if (currentMacro1 == HIGH && lastMacro1PinState == LOW) {
    animController.cycleZone();
  } else if (currentMacro2 == HIGH && lastMacro2PinState == LOW) {
    animController.cycleAnimationType();
  } else if (currentMacro3 == HIGH && lastMacro3PinState == LOW) {
    animController.cycleAnimationModifier();
  } else if (currentMacro4 == HIGH && lastMacro4PinState == LOW) {
    animController.cycleMasterBrightness();
  }
  lastMacro1PinState = currentMacro1;
  lastMacro2PinState = currentMacro2;
  lastMacro3PinState = currentMacro3;
  lastMacro4PinState = currentMacro4;
  
}