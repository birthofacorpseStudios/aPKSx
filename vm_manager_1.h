
#pragma once
#include "../ui/launcher.h"
#include <string>

namespace VmManager {
    void Init();
    void Shutdown();
    bool ExecPm(const std::string& cmd);
    std::vector<AppInfo> ListPackages();
    void LaunchPackage(const std::string& pkg);
    void SendBack();
    void InjectTouch(int type, float x, float y);
    void InjectKey(int keycode);
    // Returns RGBA pointer to Android framebuffer
    void* GetFramebuffer();
}
