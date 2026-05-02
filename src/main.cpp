#include <Arduino.h>
#include <pins.h>
#include <led_layout.h>
#include <animation_controller.h>
#include <input_parser.h>
#include <input_protocol.h>

#define BAUD_RATE 115200

const bool DEBUG_MODE = false;

enum PlayerIndex : uint8_t {
  P1_INDEX    = 0,
  P2_INDEX    = 1
};

// ---- Timing ----
const unsigned long IDLE_TIMEOUT_MS = 15UL * 60UL * 1000UL;  // 15 Minutes
const unsigned long UART_COMMUNICATION_TIMEOUT = 6UL * 1000UL; // 6 Seconds

// ------ Macro States ------
bool lastMacro1State = false;
bool lastMacro2State = false;
bool lastMacro3State = false;
bool lastMacro4State = false;

// ------ Activity States ------
unsigned long lastActivityMs  = 0;
unsigned long lastP1UartTime  = 0;
unsigned long lastP2UartTime  = 0;
bool lastActivityState          = false;
bool systemActive               = true;
bool p1Connected                = false; // Whether player 1 is connected to the system
bool p2Connected                = false; // Whether player 2 is connected to the system
bool p1Active                   = false; // Whether player 1 is currently actuating an input
bool p2Active                   = false; // Whether player 2 is currently actuating an input

AnimationController animController(IDLE_TIMEOUT_MS);
InputParser p1Parser;
InputParser p2Parser;
InputPacket p1Packet;
InputPacket p2Packet;


// local function declarations
void handleActivity();
void handleJoyIndicators();
void shutOffJoyIndicators(PlayerIndex index);
bool readP1Input();
bool readP2Input();
void handleMacroEvent(bool active, InputPacket &packet);
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

  animController.setup();
}

void loop() {
  handleActivity();
  handleJoyIndicators();
  animController.handleIdleState(systemActive);
  handleMacroEvent(p1Active, p1Packet);
  animController.processAnimations();

  delay(1); // For USB Stability
}

/**
* Updates the system activity state based on the recorded activity input state
*/
void handleActivity() {
  p1Active = readP1Input();
  p2Active = readP2Input();

  // Controller connection state:
  // If we haven't received any communication from the gamepad for the duration of
  // our timeout, then assume the gamepad has disconnected
  if (p1Connected && (millis() - lastP1UartTime) > UART_COMMUNICATION_TIMEOUT) {
    p1Connected = false;
    shutOffJoyIndicators(P1_INDEX);
  } else if (!p1Connected && (millis() - lastP1UartTime) < UART_COMMUNICATION_TIMEOUT) {
    p1Connected = true;
  }

  if (p2Connected && (millis() - lastP2UartTime) > UART_COMMUNICATION_TIMEOUT) {
    p2Connected = false;
    shutOffJoyIndicators(P2_INDEX);
  } else if (!p2Connected && (millis() - lastP2UartTime) < UART_COMMUNICATION_TIMEOUT) {
    p2Connected = true;
  }

  // System activity state:
  // If neither player has pressed an input for the duration of our idle timeout,
  // then set the system to an idle state (shut off LEDs)
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
    shutOffJoyIndicators(P1_INDEX);
    shutOffJoyIndicators(P2_INDEX);
  }
}

/**
 * Shut off all joystick indicator LEDs for the specified player
 * @param index The index corresponding to the player for which to shut off indicators
 */
void shutOffJoyIndicators(PlayerIndex index) {
  switch (index) {
    case P1_INDEX:
      animController.setLEDPinBrightness(P1_LS_MODE_PIN, 0);
      animController.setLEDPinBrightness(P1_DP_MODE_PIN, 0);
      animController.setLEDPinBrightness(P1_RS_MODE_PIN, 0);
      break;
    case P2_INDEX:
      animController.setLEDPinBrightness(P2_LS_MODE_PIN, 0);
      animController.setLEDPinBrightness(P2_DP_MODE_PIN, 0);
      animController.setLEDPinBrightness(P2_RS_MODE_PIN, 0);
      break;
  }
}

/**
 * Updates the LED indicators for joystick modes based on the current input packets for player 1 and player 2
 */
void handleJoyIndicators() {
  if (systemActive) {
    // Player 1
    if (p1Connected) {
      switch(p1Packet.joystick_mode) {
        case JOY_MODE_DPAD:
          animController.setLEDPinBrightness(P1_DP_MODE_PIN, 100);
          animController.setLEDPinBrightness(P1_LS_MODE_PIN, 0);
          animController.setLEDPinBrightness(P1_RS_MODE_PIN, 0);
          break;
        case JOY_MODE_LS:
          animController.setLEDPinBrightness(P1_DP_MODE_PIN, 0);
          animController.setLEDPinBrightness(P1_LS_MODE_PIN, 100);
          animController.setLEDPinBrightness(P1_RS_MODE_PIN, 0);
          break;
        case JOY_MODE_RS:
          animController.setLEDPinBrightness(P1_DP_MODE_PIN, 0);
          animController.setLEDPinBrightness(P1_LS_MODE_PIN, 0);
          animController.setLEDPinBrightness(P1_RS_MODE_PIN, 100);
          break;
        default:
          animController.setLEDPinBrightness(P1_DP_MODE_PIN, 0);
          animController.setLEDPinBrightness(P1_LS_MODE_PIN, 0);
          animController.setLEDPinBrightness(P1_RS_MODE_PIN, 0);
      }
    }

    if (p2Connected) {
      switch(p2Packet.joystick_mode) {
        case JOY_MODE_DPAD:
          animController.setLEDPinBrightness(P2_DP_MODE_PIN, 100);
          animController.setLEDPinBrightness(P2_LS_MODE_PIN, 0);
          animController.setLEDPinBrightness(P2_RS_MODE_PIN, 0);
          break;
        case JOY_MODE_LS:
          animController.setLEDPinBrightness(P2_DP_MODE_PIN, 0);
          animController.setLEDPinBrightness(P2_LS_MODE_PIN, 100);
          animController.setLEDPinBrightness(P2_RS_MODE_PIN, 0);
          break;
        case JOY_MODE_RS:
          animController.setLEDPinBrightness(P2_DP_MODE_PIN, 0);
          animController.setLEDPinBrightness(P2_LS_MODE_PIN, 0);
          animController.setLEDPinBrightness(P2_RS_MODE_PIN, 100);
          break;
        default:
          animController.setLEDPinBrightness(P2_DP_MODE_PIN, 0);
          animController.setLEDPinBrightness(P2_LS_MODE_PIN, 0);
          animController.setLEDPinBrightness(P2_RS_MODE_PIN, 0);
      }
    }
  }
}

/**
 * Process Player 1 UART data received
 * @return true if activity detected, false otherwise
 */
bool readP1Input() {
  static InputPacket packet;

  while (Serial1.available()) {
    lastP1UartTime = millis();
    uint8_t byte = Serial1.read();

    if (p1Parser.parseByte(byte, packet)) {
      p1Packet = packet;
      uint16_t buttons = p1Packet.buttons_l | (p1Packet.buttons_h << 8);

      if (DEBUG_MODE) {
        Serial.println("-------Player 1 Input Detected-------");
        Serial.print("Buttons: ");
        Serial.println(buttons, BIN);
        Serial.print("Joystick: ");
        Serial.println(p1Packet.joystick, BIN);
        Serial.println("-----------------------------------");
        Serial.println();
      }

      return (buttons !=0) || (p1Packet.joystick != 0); // if any buttons or joystick activity, return true
    }
  }
  return false; // no input detected
}

/**
 * Process Player 2 UART data received
 * @return true if activity detected, false otherwise
 */
bool readP2Input() {
  static InputPacket packet;

  while (Serial2.available()) {
    lastP2UartTime = millis();
    uint8_t byte = Serial2.read();

    if (p2Parser.parseByte(byte, packet)) {
      p2Packet = packet;
      uint16_t buttons = p2Packet.buttons_l | (p2Packet.buttons_h << 8);

      if (DEBUG_MODE) {
        Serial.println("-------Player 2 Input Detected-------");
        Serial.print("Buttons: ");
        Serial.println(buttons, BIN);
        Serial.print("Joystick: ");
        Serial.println(p2Packet.joystick, BIN);
        Serial.println("-----------------------------------");
        Serial.println();
      }
      return (buttons !=0) || (p2Packet.joystick != 0); // if any buttons or joystick activity, return true
    }
  }
  return false; // no input detected
}

/**
* Sets the animation state based on the triggered activity event
* @param active Whether the player has any active inputs
* @param packet The input packet to check for macro events
*/
void handleMacroEvent(bool active, InputPacket &packet) {
  if (active) { // Don't bother checking macros if there is no input
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
  } else {
    lastMacro1State = false;
    lastMacro2State = false;
    lastMacro3State = false;
    lastMacro4State = false;
  }
}