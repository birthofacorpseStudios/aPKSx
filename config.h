
#pragma once
#include <string>
struct Config {
    float pointerSensitivity = 1.5f; // 0.5 - 3.0
    float touchpadSensitivity = 1.0f;
    int deadzone = 15; // %
    bool useTouchpadAsTouch = true;
    int displayFit = 0; // 0=Fit, 1=Stretch, 2=16:9, 3=4:3 Original
    float displayScale = 1.0f; // 0.8 - 1.2
    // Button mapping - PS4 -> Android
    int mapConfirm = 0; // 0=X 1=R2
    int mapBack = 0; // 0=Circle
    std::string version = "v1.0-offline";
    void Load();
    void Save();
    static Config& Get();
};
