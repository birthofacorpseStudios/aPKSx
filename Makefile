
TARGET := APKStation
TITLE_ID := APKSTATION01
TITLE := APKStation - Offline APK Launcher
CONTENT_ID := IV0000-APKSTATION01_00-APKSTATION001
VERSION := 01.00

CC := $(OO)/bin/clang
CXX := $(OO)/bin/clang++
OO := /opt/openorbis
# Allow env override
ifneq ($(OO_PS4_TOOLCHAIN),)
OO := $(OO_PS4_TOOLCHAIN)
endif
ifneq ($(OPENORBIS),)
OO := $(OPENORBIS)
endif

CXXFLAGS := -std=c++17 -O2 -I$(OO)/include -I. -DORBIS -D__PS4__ -fno-stack-protector -fno-exceptions -fPIC
CFLAGS := -O2 -I$(OO)/include -DORBIS -fPIC
LDFLAGS := -L$(OO)/lib -lScePad -lSceUserService -lSceSystemService -lSceSysmodule -lSceCommonDialog -lSceVideoOut -lSceGnmDriver -lSceFreeType -lScePiglet -lSceNet -lSceNetCtl -lSceFios2 -lSceLibcInternal -lkernel -lc -lc++ -lm

SRC := main.cpp pad.cpp filesystem.cpp config.cpp pointer.cpp launcher.cpp apk_manager.cpp vm_manager.cpp
OBJS := $(SRC:.cpp=.o)

all: $(CONTENT_ID).pkg

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) -Wl,-T,$(OO)/link.x

eboot.bin: $(TARGET).elf
	$(OO)/bin/create-fself -in=$< -out=$(TARGET).oelf -eboot=$@ --paid 0x3800000000000011

gp4: eboot.bin
	mkdir -p sce_sys
	cp param.json sce_sys/param.json || echo '{ "Title":"$(TITLE)", "TitleId":"$(TITLE_ID)" }' > sce_sys/param.json
	cp icon0.png sce_sys/icon0.png
	cp pic0.png sce_sys/pic0.png || cp icon0.png sce_sys/pic0.png
	cp pic1.png sce_sys/pic1.png || cp icon0.png sce_sys/pic1.png
	mkdir -p assets/images
	cp bg_main.png assets/images/bg_main.png 2>/dev/null || cp bg.png assets/images/bg_main.png 2>/dev/null || cp icon0.png assets/images/bg_main.png
	cp icon_app.png assets/images/icon_app.png 2>/dev/null || cp icon0.png assets/images/icon_app.png
	$(OO)/bin/create-gp4 --content-id=$(CONTENT_ID) --path=eboot.bin --sce_sys_dir=sce_sys --sce_module_dir=sce_module --extra_path=assets --gp4=project.gp4 || $(OO)/bin/create-gp4 --content-id=$(CONTENT_ID) --gp4=project.gp4 eboot.bin sce_sys/ || true

$(CONTENT_ID).pkg: gp4
	$(OO)/bin/PkgTool.Core --cli gp4 project.gp4 --out $@ || $(OO)/bin/create-pkg --content-id=$(CONTENT_ID) --title="$(TITLE)" --title-id=$(TITLE_ID) --gp4=project.gp4 -o $@ || dotnet $(OO)/bin/PkgTool.Core.dll --cli gp4 project.gp4 --out $@ || echo "Trying alternative pkg creation" && $(OO)/bin/PkgTool.Core pkg_build project.gp4 . || true
	ls -lh *.pkg || echo "PKG not yet, checking"
	if [ ! -f $@ ]; then echo "Trying pkg from PkgTool" && ls -lh *.pkg && find . -name "*.pkg" | head; fi

clean:
	rm -rf $(OBJS) *.elf *.oelf eboot.bin *.pkg project.gp4 sce_sys assets pkg
