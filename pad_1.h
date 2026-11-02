
#pragma once
#include <cstdint>
#define ORBIS_PAD_L3 0x00000002
#define ORBIS_PAD_R3 0x00000004
#define ORBIS_PAD_OPTIONS 0x00000008
#define ORBIS_PAD_UP 0x00000010
#define ORBIS_PAD_RIGHT 0x00000020
#define ORBIS_PAD_DOWN 0x00000040
#define ORBIS_PAD_LEFT 0x00000080
#define ORBIS_PAD_L2 0x00000100
#define ORBIS_PAD_R2 0x00000200
#define ORBIS_PAD_L1 0x00000400
#define ORBIS_PAD_R1 0x00000800
#define ORBIS_PAD_TRIANGLE 0x00001000
#define ORBIS_PAD_CIRCLE 0x00002000
#define ORBIS_PAD_CROSS 0x00004000
#define ORBIS_PAD_SQUARE 0x00008000

struct OrbisPadData {
    uint32_t buttons;
    uint32_t buttons_pressed;
    float lx, ly, rx, ry;
    float l2, r2;
};

namespace Pad {
    void Init();
    void Shutdown();
    void Update();
    OrbisPadData Get(int idx);
}
