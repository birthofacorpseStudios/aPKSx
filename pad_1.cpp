
#include "pad.h"
#include <orbis/Pad.h>

static int padHandle = -1;

void Pad::Init() {
    OrbisPadInitParam param{};
    param.proParam.params = 0;
    scePadInit();
    padHandle = scePadOpen(0, 0, 0, nullptr);
}

void Pad::Shutdown() {
    if (padHandle >= 0) scePadClose(padHandle);
    scePadFini();
}

static OrbisPadData last{};
void Pad::Update() {
    OrbisPadData d{};
    scePadReadState(padHandle, nullptr);
}

OrbisPadData Pad::Get(int idx) {
    // Stub wired to real scePadRead - replace with actual read logic
    OrbisPadData d{};
    OrbisPadData2 pad{};
    scePadRead(padHandle, &pad, 1);
    d.buttons = pad.buttons;
    d.lx = (pad.leftStick.x - 128) / 128.0f;
    d.ly = (pad.leftStick.y - 128) / 128.0f;
    d.l2 = pad.analogButtons.l2 / 255.0f;
    d.r2 = pad.analogButtons.r2 / 255.0f;
    d.buttons_pressed = d.buttons & ~last.buttons;
    last = d;
    return d;
}
