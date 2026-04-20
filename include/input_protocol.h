#ifndef input_protocol_h
#define input_protocol_h

#include <Arduino.h>

// -----------------------------
// Packet constants
// -----------------------------
#define INPUT_HEADER1 0xAA
#define INPUT_HEADER2 0x55
#define INPUT_PACKET_SIZE 8
#define MAX_JOYSTICK_VALUE 0x0F // Assuming all 4 directions are pressed simultaneously
#define MAX_JOYSTICK_MODE_VALUE 0X02;

// ------------------ Buttons ----------------- //

enum ButtonBit : uint16_t {
    B1_BIT              = (1 << 0),
    B2_BIT              = (1 << 1),
    B3_BIT              = (1 << 2),
    B4_BIT              = (1 << 3),
    L1_BIT              = (1 << 4),
    R1_BIT              = (1 << 5),
    L2_BIT              = (1 << 6),
    R2_BIT              = (1 << 7),
    SELECT_BIT          = (1 << 8),
    START_BIT           = (1 << 9),
    HOME_BIT            = (1 << 10),
    EXTRA1_BIT          = (1 << 11),
    EXTRA2_BIT          = (1 << 12)
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

#endif