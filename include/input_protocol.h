#ifndef input_protocol_h
#define input_protocol_h

#include <Arduino.h>

// -----------------------------
// Packet constants
// -----------------------------
#define INPUT_HEADER1 0xAA
#define INPUT_HEADER2 0x55
#define MAX_PAYLOAD 16  // safety cap
#define INPUT_PACKET_SIZE 8

const uint8_t MAX_JOYSTICK_VALUE = 0x0F; // Assuming all 4 directions are pressed simultaneously
const uint8_t MAX_JOYSTICK_MODE_VALUE = 0x02;

// -----------------------------
// Packet struct
// -----------------------------
typedef struct {
    uint8_t header;         // 0xAA for packet start
    uint8_t header2;        // 0x55 for additional sync robustness
    uint8_t length;         // payload size (should be 4 for buttons + joystick + mode)
    uint8_t buttons_l;
    uint8_t buttons_h;
    uint8_t joystick;
    uint8_t joystick_mode;
    uint8_t checksum;
} __attribute__((packed)) InputPacket;

// ------------------ Buttons ----------------- //

enum ButtonBit : uint16_t {
    B1_BIT              = (1 << 0),     // A/X
    B2_BIT              = (1 << 1),     // B/O
    B3_BIT              = (1 << 2),     // X/□
    B4_BIT              = (1 << 3),     // Y/△
    L1_BIT              = (1 << 4),     // L1/LB
    R1_BIT              = (1 << 5),     // R1/RB
    L2_BIT              = (1 << 6),     // L2/LT
    R2_BIT              = (1 << 7),     // R2/RT
    SELECT_BIT          = (1 << 8),     // Select/Share
    START_BIT           = (1 << 9),     // Start/Options
    HOME_BIT            = (1 << 10),    // Guide/PS
    EXTRA1_BIT          = (1 << 11),    // In-App Guide/PS
    EXTRA2_BIT          = (1 << 12)     // Record
};

// ------------------ Joystick ----------------- //
enum JoystickBit : uint8_t {
    JOY_UP_BIT          = (1 << 0),
    JOY_DOWN_BIT        = (1 << 1),
    JOY_LEFT_BIT        = (1 << 2),
    JOY_RIGHT_BIT       = (1 << 3)
};

// ------------------- Joystick Mode ----------------- //
enum JoystickModeBit : uint8_t {
    JOY_MODE_DPAD       = (0 << 0),
    JOY_MODE_LS         = (1 << 0),
    JOY_MODE_RS         = (1 << 1)
};

#endif