#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xc8];
    s32 entryCount;
    u8 pad_0CC[0x20];
    s32 entryIndex;
    s32 prevEntryIndex;
    u8 pad_0F4[0x8];
    s32 state;
    u8 pad_100[0x8];
    s32 idleCount;
} FieldMenu;

extern BOOL IsModeSetOrFlag370aClear(void);
extern BOOL IsHudFlag7Set(void);
extern BOOL IsFieldFlag10Set(void);
extern void *func_ov001_02075348(FieldMenu *menu, s32 index, s32 slot, s32 *outValue);

BOOL FieldMenu_TryEnterState3(FieldMenu *menu)
{
    if (menu->entryCount < 2) {
        return FALSE;
    }
    if (!IsModeSetOrFlag370aClear() || IsHudFlag7Set() || IsFieldFlag10Set()) {
        return FALSE;
    }
    menu->state = 3;
    menu->idleCount = 0;
    menu->prevEntryIndex = menu->entryIndex;
    func_ov001_02075348(menu, menu->entryIndex, 0, &menu->entryIndex);
    return TRUE;
}
