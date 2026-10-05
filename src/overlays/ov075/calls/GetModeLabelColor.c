#include "nitro/types.h"

typedef struct MatrixMenu {
    u8 pad_00000[0x13e64];
    u16 phase;
    u8 pad_13e66[0x13e74 - 0x13e66];
    u32 phaseTimer;
    u8 pad_13e78[0x13ea0 - 0x13e78];
    int currentMode;
} MatrixMenu;

extern BOOL IsMenuModeUnlocked(int mode);

u16 GetModeLabelColor(MatrixMenu *menu, int mode)
{
    if (menu->currentMode == mode) {
        return 0x77bd;
    }
    if (IsMenuModeUnlocked(mode) && ((menu->phase & ~0xff) != 0x600 || menu->phaseTimer > 0x10)) {
        return 0x7fff;
    }
    return 0x3def;
}