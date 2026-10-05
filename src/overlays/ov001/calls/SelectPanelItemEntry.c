#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x58];
    s32 low : 16;
    s32 itemId : 11;
    s32 high : 5;
} Panel;

extern void func_ov001_02078800(int entry);

void SelectPanelItemEntry(Panel *panel) {
    int entry = -1;
    int itemId = panel->itemId;
    switch (itemId) {
    case 0x1f0:
    case 0x1f1:
    case 0x1f2:
    case 0x1f3:
        entry = itemId - 0x117;
        break;
    }
    func_ov001_02078800(entry);
}
