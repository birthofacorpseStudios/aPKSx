
#pragma once
#include "../core/pad.h"

struct Pointer {
    float x = 960, y = 540;
    bool isClicking = false;
    float clickTime = 0;
    void update(const OrbisPadData& pad);
};

