
#include "pointer.h"
#include <algorithm>

void Pointer::update(const OrbisPadData& pad) {
    const float dead = 0.15f;
    float lx = (fabs(pad.lx) > dead) ? pad.lx : 0;
    float ly = (fabs(pad.ly) > dead) ? pad.ly : 0;

    // Speed scales with stick deflection + L1 for precision
    float speed = 12.0f;
    if (pad.buttons & 0x400) speed = 4.0f; // L1 slow mode

    x += lx * speed;
    y += ly * speed;
    x = std::clamp(x, 0.0f, 1920.0f);
    y = std::clamp(y, 0.0f, 1080.0f);

    isClicking = (pad.buttons & 0x0000200) || (pad.buttons & 0x00004000); // R2 or X
}
