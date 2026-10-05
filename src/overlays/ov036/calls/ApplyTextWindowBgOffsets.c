#include "nitro/types.h"

#define REG_BG2OFS (*(vu32 *)0x04000018)
#define REG_BG3OFS (*(vu32 *)0x0400001c)

typedef struct TextWindowEntry {
    u8 pad_00[0x14];
    s32 scrollX;
    s32 scrollY;
    u8 pad_1C[0x8];
    s32 bgLayer;
    u8 pad_28[0xe8];
} TextWindowEntry;

typedef struct OverlayWork {
    u8 pad_0000[0x64fc];
    TextWindowEntry windows[3];
} OverlayWork;

extern OverlayWork *gTextWindowResourceTable;
extern BOOL func_ov036_020c280c(TextWindowEntry *entry);

void ApplyTextWindowBgOffsets(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        TextWindowEntry *entry = &gTextWindowResourceTable->windows[i];
        if (func_ov036_020c280c(entry)) {
            int offsetX = -entry->scrollX;
            int offsetY = -entry->scrollY;
            if (entry->bgLayer == 2) {
                REG_BG2OFS = (u32)((offsetX & 0x1ff) | ((offsetY << 16) & 0x01ff0000));
            } else {
                REG_BG3OFS = (u32)((offsetX & 0x1ff) | ((offsetY << 16) & 0x01ff0000));
            }
        }
    }
}
