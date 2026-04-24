#include <Arduino.h>
#include <pins.h>
#include <led_layout.h>
#include <animation_controller.h>
#include <input_parser.h>
#include <input_protocol.h>

// UART Communication
#include "hardware/uart.h"
#include "hardware/gpio.h"

#define UART_ID uart0
#define BAUD_RATE 115200

const bool DEBUG_MODE = false;

// ---- Timing ----
const unsigned long IDLE_TIMEOUT_MS = 15UL * 60UL * 1000UL;  // 15 Minutes

// For Testing
const unsigned long CYCLE_MOD_MS = 5UL * 1000UL;    // 5 Seconds
const unsigned long CYCLE_TYPE_MS = 35UL * 1000UL;  // 35 Seconds
const unsigned long CYCLE_ZONE_MS = 35UL * 1000UL;  // 35 Seconds

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
InputParser parser;


// local function declarations
void handleUARTActivity();
// void handleActivity();
// void handleMacroEvent();
void updateActivityState(bool active);
void printHex8Label(const char* label, uint8_t value);

void setup() {
  delay(100); // allow USB stack to settle

  // UART Initialization
  Serial.begin(BAUD_RATE);
  Serial1.setRX(P2_UART_RX_PIN);        // match your wiring
  Serial1.begin(BAUD_RATE);    // UART from GP2040

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
  handleUARTActivity();
  // handleActivity();
  animController.handleIdleState(systemActive);
  // handleMacroEvent();
  if (DEBUG_MODE) {
    if ((millis() - lastZoneSwitch) > CYCLE_ZONE_MS) {
      Serial.println("Cycling Zone...");
      animController.cycleZone();
      lastZoneSwitch = millis();
      lastModSwitch = millis();
    }
    if ((millis() - lastModSwitch) > CYCLE_MOD_MS) {
      Serial.println("Cycling Modifier...");
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
 * Process UART data received
 */
void handleUARTActivity() {
  InputPacket packet;

  while (Serial1.available()) {
    uint8_t byte = Serial1.read();

    if (parser.parseByte(byte, packet)) {
      Serial.println("Received valid packet");

      uint16_t buttons = packet.buttons_l | (packet.buttons_h << 8);

      if (DEBUG_MODE) {
        Serial.println();
        Serial.println("---- PACKET DETAILS ----");
        printHex8Label("Header", packet.header);
        printHex8Label("Header2", packet.header2);
        printHex8Label("Buttons_l", packet.buttons_l);
        printHex8Label("Buttons_h", packet.buttons_h);
        printHex8Label("Joystick", packet.joystick);
        printHex8Label("Joystick Mode", packet.joystick_mode);
        Serial.println("---------------------------");
        Serial.println();
      }

      // Example usage:
      if (packet.joystick_mode == JOY_MODE_DPAD) {
        Serial.println("Joystick in DPAD mode");
        animController.setLEDPinBrightness(P1_DP_MODE_PIN, 100);
        animController.setLEDPinBrightness(P1_LS_MODE_PIN, 0);
        animController.setLEDPinBrightness(P1_RS_MODE_PIN, 0);
      } else if (packet.joystick_mode == JOY_MODE_LS) {
        Serial.println("Joystick in Left Stick mode");
        animController.setLEDPinBrightness(P1_DP_MODE_PIN, 0);
        animController.setLEDPinBrightness(P1_LS_MODE_PIN, 100);
        animController.setLEDPinBrightness(P1_RS_MODE_PIN, 0);
      } else if (packet.joystick_mode == JOY_MODE_RS) {
        Serial.println("Joystick in Right Stick mode");
        animController.setLEDPinBrightness(P1_DP_MODE_PIN, 0);
        animController.setLEDPinBrightness(P1_LS_MODE_PIN, 0);
        animController.setLEDPinBrightness(P1_RS_MODE_PIN, 100);
      }
      Serial.println();
    }
  }
}

/**
 * Prints bytes in hex format with a label for debugging purposes
 * @param label A string label to describe the value being printed
 * @param value The byte value to print in hex
 */
void printHex8Label(const char* label, uint8_t value) {
  Serial.print(label);
  Serial.print(": 0x");
  if (value < 0x10) Serial.print("0"); // leading zero for single-digit hex
  Serial.println(value, HEX);
}

// /**
// * Sets the animation state based on the triggered activity event
// */
// void handleMacroEvent() {
//   PinStatus currentMacro1 = digitalRead(MACRO_1_PIN);
//   PinStatus currentMacro2 = digitalRead(MACRO_2_PIN);
//   PinStatus currentMacro3 = digitalRead(MACRO_3_PIN);
//   PinStatus currentMacro4 = digitalRead(MACRO_4_PIN);

//   if (currentMacro1 == HIGH && lastMacro1PinState == LOW) {
//     animController.cycleZone();
//   } else if (currentMacro2 == HIGH && lastMacro2PinState == LOW) {
//     animController.cycleAnimationType();
//   } else if (currentMacro3 == HIGH && lastMacro3PinState == LOW) {
//     animController.cycleAnimationModifier();
//   } else if (currentMacro4 == HIGH && lastMacro4PinState == LOW) {
//     animController.cycleMasterBrightness();
//   }
//   lastMacro1PinState = currentMacro1;
//   lastMacro2PinState = currentMacro2;
//   lastMacro3PinState = currentMacro3;
//   lastMacro4PinState = currentMacro4;
// }