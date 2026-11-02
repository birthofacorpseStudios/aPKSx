
#include "launcher.h"
#include "../core/filesystem.h"
#include "../android/apk_manager.h"
#include "../android/vm_manager.h"
#include <cstdio>

// Simplified render - replace with Piglet/ImGui draw calls
void Launcher::init() {
    refreshInstalled();
}

void Launcher::refreshInstalled() {
    installedApps = ApkManager::GetInstalledApps();
}

void Launcher::update(const OrbisPadData& pad, const Pointer& pointer) {
    // Navigation logic
    if (state == GRID) {
        if (pad.buttons_pressed & 0x00000010) selectedIdx--; // UP
        if (pad.buttons_pressed & 0x00000040) selectedIdx++; // DOWN
        if (pad.buttons_pressed & 0x00004000) { // X to launch
            if (selectedIdx >=0 && selectedIdx < installedApps.size())
                launchApp(installedApps[selectedIdx]);
        }
        if (pad.buttons_pressed & 0x00000008) state = HAMBURGER; // OPTIONS = hamburger
    } else if (state == HAMBURGER) {
        // Menu: Install / Uninstall
        if (pad.buttons_pressed & 0x00002000) state = GRID; // Circle back
    }
}

void Launcher::render(const Pointer& pointer) {
    // TODO: Piglet rendering
    // 1. Draw grid of installedApps with icons from /data/APKStation/apps/<pkg>/icon.png
    // 2. If state==HAMBURGER draw side drawer with ≡ menu
    // 3. If RUNNING_APP draw Android framebuffer texture from VmManager::GetFramebuffer()
    // 4. Always draw pointer cursor at pointer.x, pointer.y
}

void Launcher::launchApp(const AppInfo& app) {
    VmManager::LaunchPackage(app.packageName);
    inApp = true;
    state = RUNNING_APP;
}

void Launcher::exitApp() {
    VmManager::SendBack();
    // If still in app after 500ms, kill activity
    inApp = false;
    state = GRID;
}
