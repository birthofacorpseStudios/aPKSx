
#include <cstdio>
#include <orbis/libkernel.h>
#include <orbis/Sysmodule.h>
#include "core/pad.h"
#include "core/filesystem.h"
#include "ui/launcher.h"
#include "ui/filebrowser.h"
#include "ui/pointer.h"
#include "android/apk_manager.h"
#include "android/vm_manager.h"

int main() {
    sceSysmoduleLoadModule(ORBIS_SYSMODULE_PAD);
    sceSysmoduleLoadModule(ORBIS_SYSMODULE_SYSTEM_SERVICE);

    Pad::Init();
    FileSystem::Init();
    ApkManager::Init();
    VmManager::Init(); // Starts QEMU Android container in background thread

    Launcher launcher;
    launcher.init();

    Pointer pointer;
    bool running = true;

    while (running) {
        Pad::Update();
        auto pad = Pad::Get(0);

        pointer.update(pad);

        // Circle = exit to PS4 home
        if (pad.buttons_pressed & ORBIS_PAD_CIRCLE) {
            if (launcher.isInApp()) {
                launcher.exitApp(); // sends BACK to Android
            } else {
                // If in launcher root and circle held
                if (pad.buttons & ORBIS_PAD_CIRCLE) {
                    // Will exit after 1 sec hold - handled in launcher
                }
            }
        }

        launcher.update(pad, pointer);
        launcher.render(pointer);

        sceKernelUsleep(16666); // ~60fps
    }

    VmManager::Shutdown();
    Pad::Shutdown();
    return 0;
}
