
#pragma once
#include "../core/pad.h"
#include "pointer.h"
#include <vector>
#include <string>

struct AppInfo {
    std::string packageName;
    std::string label;
    std::string apkPath;
    std::string iconPath;
};

class Launcher {
public:
    void init();
    void update(const OrbisPadData& pad, const Pointer& pointer);
    void render(const Pointer& pointer);

    bool isInApp() const { return inApp; }
    void launchApp(const AppInfo& app);
    void exitApp();

    // Menu states
    enum State { GRID, HAMBURGER, INSTALL_LIST, UNINSTALL_LIST, RUNNING_APP };
    State state = GRID;
private:
    std::vector<AppInfo> installedApps;
    bool inApp = false;
    void refreshInstalled();
    int selectedIdx = 0;
};
