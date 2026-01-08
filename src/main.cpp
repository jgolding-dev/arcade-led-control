#include <Arduino.h>
#include <animation_controller.h>
#include <leds.h>

const bool DEBUG_MODE = true;

const int ACTIVITY_PIN = 4;  // GPIO connected to ActivityPulse
const int MACRO_1_PIN  = 5;   // GPIO connected to Macro1 (Cycle Animation Zone)
const int MACRO_2_PIN  = 6;   // GPIO connected to Macro2 (Cycle Animation Type)
const int MACRO_3_PIN  = 7;   // GPIO connected to Macro3 (Cycle Animation Modifier)
const int MACRO_4_PIN  = 8;  // GPIO connected to Macro4 (Cycle Brightness Level)

// const int INPUT_PINS = { ACTIVITY_PIN, MACRO_1_PIN, MACRO_2_PIN, MACRO_3_PIN, MACRO_4_PIN };

// ---- Timing ----
const unsigned long IDLE_TIMEOUT_MS = 10UL * 60UL * 1000UL;  // 10 Minutes

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

AnimationController* animController = new AnimationController(IDLE_TIMEOUT_MS);


// local function declarations
void handleActivity();
void handleMacroEvent();
void updateIdleState();

void setup() {
  if (DEBUG_MODE) {
    Serial.begin(9600);
  }
  // Initialize LED output pins
  Leds::initPins();

  // Initialize activity input pins
  pinMode(ACTIVITY_PIN, INPUT_PULLDOWN);
  pinMode(MACRO_1_PIN, INPUT_PULLDOWN);
  pinMode(MACRO_2_PIN, INPUT_PULLDOWN);
  pinMode(MACRO_3_PIN, INPUT_PULLDOWN);
  pinMode(MACRO_4_PIN, INPUT_PULLDOWN);


  // Set last activity time and update state
  lastActivityMs = millis();
  systemActive = true;
  animController->setup();
}

void loop() {
  handleActivity();
  animController->handleIdleState(systemActive);
  handleMacroEvent();
  if (DEBUG_MODE) {
    if ((millis() - lastZoneSwitch) > CYCLE_ZONE_MS) {
      Serial.println("Cycling Zone...");
      delay(50);
      animController->cycleZone();
      lastZoneSwitch = millis();
      lastModSwitch = millis();
    }
    else if ((millis() - lastModSwitch) > CYCLE_MOD_MS) {
      Serial.println("Cycling Modifier...");
      delay(50);
      animController->cycleAnimationModifier();
      lastModSwitch = millis();
    }
  }
  animController->processAnimations();
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
    animController->cycleZone();
  } else if (currentMacro2 == HIGH && lastMacro2PinState == LOW) {
    animController->cycleAnimationType();
  } else if (currentMacro3 == HIGH && lastMacro3PinState == LOW) {
    animController->cycleAnimationModifier();
  } else if (currentMacro4 == HIGH && lastMacro4PinState == LOW) {
    animController->cycleAnimationBrightness();
  }
  lastMacro1PinState = currentMacro1;
  lastMacro2PinState = currentMacro2;
  lastMacro3PinState = currentMacro3;
  lastMacro4PinState = currentMacro4;

  // Example macro
  // updateAnimationState(ANIM_SOLID_WHITE);
}