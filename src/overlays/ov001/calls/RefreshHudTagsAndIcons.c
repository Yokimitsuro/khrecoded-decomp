#include "nitro/types.h"

typedef struct HudScreen {
    u8 pad_000[0x1c];
    u8 tracker[0x60c - 0x1c];
    int slotIcons[2];
} HudScreen;

extern BOOL func_ov001_020645c8(u32 value);
extern int func_ov001_02064784(void);
extern signed char func_ov001_02068084(void);
extern void LoadSlotIconGraphics(int slot, int iconId);
extern BOOL IsHudFlag7Set(void);
extern BOOL IsHudFlag9Set(void);
extern BOOL IsFieldFlag8Set(void);
extern BOOL IsFieldFlag10Set(void);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8230(void *tracker, void *record);

void RefreshHudTagsAndIcons(HudScreen *hud)
{
    int i;

    func_ov027_020b8230(hud->tracker, FindActiveRecordById(hud->tracker, 0x32));
    if (func_ov001_02068084() == 0 && func_ov001_020645c8(0x3520)) {
        return;
    }
    func_ov027_020b8230(hud->tracker, FindActiveRecordById(hud->tracker, 7));
    func_ov027_020b8230(hud->tracker, FindActiveRecordById(hud->tracker, 0));
    if (!IsHudFlag7Set() && !IsFieldFlag10Set() && !IsFieldFlag8Set()
        && !IsHudFlag9Set() && (func_ov001_02064784() || !func_ov001_020645c8(0x3708))) {
        func_ov027_020b8230(hud->tracker, FindActiveRecordById(hud->tracker, 10));
        func_ov027_020b8230(hud->tracker, FindActiveRecordById(hud->tracker, 11));
    }
    for (i = 0; i < 2; i++) {
        if (hud->slotIcons[i] == -1) {
            return;
        }
        LoadSlotIconGraphics(i, hud->slotIcons[i]);
    }
}
