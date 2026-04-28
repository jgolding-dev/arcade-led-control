#include <Arduino.h>
#include <pins.h>
#include <led_layout.h>
#include <animation_controller.h>
#include <input_parser.h>
#include <input_protocol.h>

#define BAUD_RATE 115200

const bool DEBUG_MODE = false;

// ---- Timing ----
const unsigned long IDLE_TIMEOUT_MS = 15UL * 60UL * 1000UL;  // 15 Minutes

// ------ Macro States ------
bool lastMacro1State = false;
bool lastMacro2State = false;
bool lastMacro3State = false;
bool lastMacro4State = false;

// ------ Activity States ------
unsigned long lastActivityMs    = 0;
unsigned long lastP1PacketTime  = 0;
unsigned long lastP2PacketTime  = 0;
bool lastActivityState          = false;
bool systemActive               = true;

AnimationController animController(IDLE_TIMEOUT_MS);
InputParser p1Parser;
InputParser p2Parser;
InputPacket p1Packet;
InputPacket p2Packet;


// local function declarations
void handleActivity();
bool readP1Input();
bool readP2Input();
void handleMacroEvent(InputPacket &packet);
void updateActivityState(bool active);

void setup() {
  delay(100); // allow USB stack to settle

  // Initialize I/O
  Pins::initPins();

  // Debug Serial Initialization
  Serial.begin(BAUD_RATE);

  // P1 UART Initialization
  Serial1.setRX(P1_UART_RX_PIN);
  Serial1.begin(BAUD_RATE);    // UART from P1 controller board
  
  // P2 UART Initialization
  Serial2.setRX(P2_UART_RX_PIN);
  Serial2.begin(BAUD_RATE);    // UART from P2 controller board

  // Set activity states
  lastActivityMs    = 0;
  lastP1PacketTime  = 0;
  lastP2PacketTime  = 0;
  systemActive      = true;

  animController.setup();
}

void loop() {
  handleActivity();
  animController.handleIdleState(systemActive);
  handleMacroEvent(p1Packet);
  animController.processAnimations();

  delay(1); // For USB Stability
}

/**
* Updates the system activity state based on the recorded activity input state
*/
void handleActivity() {
  bool p1Active = readP1Input();
  bool p2Active = readP2Input();

  if ((p1Active || p2Active) && !lastActivityState) {
    updateActivityState(true);
  } else if (systemActive && (millis() - lastActivityMs) > IDLE_TIMEOUT_MS) {
    updateActivityState(false);
  }

  lastActivityState = p1Active || p2Active ? true : false;
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
 * Process Player 1 UART data received
 * @return true if activity detected, false otherwise
 */
bool readP1Input() {
  static InputPacket packet;
  bool inputDetected = false;

  if (Serial1.available()) {
    uint8_t byte = Serial1.read();

    if (p1Parser.parseByte(byte, packet)) {
      p1Packet = packet;
      uint16_t buttons = p1Packet.buttons_l | (p1Packet.buttons_h << 8);

      if (buttons != 0) {
        inputDetected = true;
        if (DEBUG_MODE) {
          Serial.print("Buttons: ");
          Serial.println(buttons, BIN);
        }
      }
      if (p1Packet.joystick != 0) {
        inputDetected = true;
        if (DEBUG_MODE) {
          Serial.print("Joystick: ");
          Serial.println(p1Packet.joystick, BIN);
          Serial.println();
        }
      }

      // set LED indicators for joystick mode
      if (p1Packet.joystick_mode == JOY_MODE_DPAD) {
        animController.setLEDPinBrightness(P1_DP_MODE_PIN, 100);
        animController.setLEDPinBrightness(P1_LS_MODE_PIN, 0);
        animController.setLEDPinBrightness(P1_RS_MODE_PIN, 0);
      } else
      if (p1Packet.joystick_mode == JOY_MODE_LS) {
        animController.setLEDPinBrightness(P1_DP_MODE_PIN, 0);
        animController.setLEDPinBrightness(P1_LS_MODE_PIN, 100);
        animController.setLEDPinBrightness(P1_RS_MODE_PIN, 0);
      } else if (p1Packet.joystick_mode == JOY_MODE_RS) {
        animController.setLEDPinBrightness(P1_DP_MODE_PIN, 0);
        animController.setLEDPinBrightness(P1_LS_MODE_PIN, 0);
        animController.setLEDPinBrightness(P1_RS_MODE_PIN, 100);
      }
    }
  }
  return inputDetected;
}

/**
 * Process Player 2 UART data received
 * @return true if activity detected, false otherwise
 */
bool readP2Input() {
  static InputPacket packet;
  bool inputDetected = false;

  if (Serial2.available()) {
    uint8_t byte = Serial2.read();

    if (p2Parser.parseByte(byte, packet)) {
      p2Packet = packet;
      uint16_t buttons = p2Packet.buttons_l | (p2Packet.buttons_h << 8);

      if (buttons != 0) {
        inputDetected = true;
        if (DEBUG_MODE) {
          Serial.print("Buttons: ");
          Serial.println(buttons, BIN);
        }
      }
      if (p2Packet.joystick != 0) {
        inputDetected = true;
        if (DEBUG_MODE) {
          Serial.print("Joystick: ");
          Serial.println(p2Packet.joystick, BIN);
          Serial.println();
        }
      }

      // set LED indicators for joystick mode
      if (p2Packet.joystick_mode == JOY_MODE_DPAD) {
        animController.setLEDPinBrightness(P2_DP_MODE_PIN, 100);
        animController.setLEDPinBrightness(P2_LS_MODE_PIN, 0);
        animController.setLEDPinBrightness(P2_RS_MODE_PIN, 0);
      } else
      if (p2Packet.joystick_mode == JOY_MODE_LS) {
        animController.setLEDPinBrightness(P2_DP_MODE_PIN, 0);
        animController.setLEDPinBrightness(P2_LS_MODE_PIN, 100);
        animController.setLEDPinBrightness(P2_RS_MODE_PIN, 0);
      } else if (p2Packet.joystick_mode == JOY_MODE_RS) {
        animController.setLEDPinBrightness(P2_DP_MODE_PIN, 0);
        animController.setLEDPinBrightness(P2_LS_MODE_PIN, 0);
        animController.setLEDPinBrightness(P2_RS_MODE_PIN, 100);
      }
    }
  }
  return inputDetected;
}

/**
* Sets the animation state based on the triggered activity event
* @param packet The input packet to check for macro events
*/
void handleMacroEvent(InputPacket &packet) {
  uint16_t buttons = packet.buttons_l | (packet.buttons_h << 8);
  bool macro1State = ((buttons & SELECT_BIT) && (buttons & B3_BIT)) ? true : false; // Select + X/□
  bool macro2State = ((buttons & SELECT_BIT) && (buttons & B4_BIT)) ? true : false; // Select + Y/△
  bool macro3State = ((buttons & SELECT_BIT) && (buttons & R1_BIT)) ? true : false; // Select + R1/RB
  bool macro4State = ((buttons & SELECT_BIT) && (buttons & L1_BIT)) ? true : false; // Select + L1/LB

  if (macro1State && !lastMacro1State) {
    animController.cycleZone();
  } else if (macro2State && !lastMacro2State) {
    animController.cycleAnimationType();
  } else if (macro3State && !lastMacro3State) {
    animController.cycleAnimationModifier();
  } else if (macro4State && !lastMacro4State) {
    animController.cycleMasterBrightness();
  }
  
  lastMacro1State = macro1State;
  lastMacro2State = macro2State;
  lastMacro3State = macro3State;
  lastMacro4State = macro4State;
}