#include "nitro/types.h"

typedef struct StatusFlags {
    u8 pad_00[8];
    u16 flags;
} StatusFlags;

typedef struct MatrixMenu {
    u8 pad_00[0x50];
    int pendingLow;
    int pendingHigh;
    u8 pad_58[0x68 - 0x58];
    int forceReady;
    u8 pad_6c[0x12dc0 - 0x6c];
    StatusFlags *status;
} MatrixMenu;

BOOL IsMatrixInputReady(MatrixMenu *menu)
{
    if ((menu->pendingLow | menu->pendingHigh) == 0 && (menu->forceReady != 0 || !(menu->status->flags & 1))) {
        return TRUE;
    }
    menu->pendingHigh = 0;
    menu->pendingLow = 0;
    return FALSE;
}