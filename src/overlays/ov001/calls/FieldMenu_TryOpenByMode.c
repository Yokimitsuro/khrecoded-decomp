#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xC8];
    s32 entryCount;
    u8 pad_0CC[0x8];
    s32 subMode;
    u8 pad_0D8[0x14];
    s32 cursorIndex;
    u8 pad_0F0[0xC];
    s32 state;
    s32 transition;
    u8 pad_104[0x4];
    s32 timer;
    u8 pad_10C[0x28];
    s32 pendingConfirm;
    s32 active;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

typedef struct {
    u8 pad_00[0x2C];
    s32 enabled;
} FieldMenuEntry;

typedef struct {
    u8 pad[0x2878];
    u32 unk0 : 18;
    u32 menuMode : 2;
} GameState;

extern FieldMenuHandle data_ov001_020a04d0;
extern GameState *data_0205fe0c;

extern BOOL IsModeSetOrFlag370aClear(void);
extern BOOL IsHudFlag7Set(void);
extern BOOL IsFieldFlag10Set(void);
extern BOOL IsLeadEntryFlag80Set(void);
extern FieldMenuEntry *CycleMenuEntry(FieldMenu *menu, s32 group, s32 slot, s32 *outIndex);
extern void func_ov001_02075d74(FieldMenu *menu, int alternate);
extern BOOL func_ov001_02077ef4(void);

BOOL FieldMenu_TryOpenByMode(void) {
    FieldMenu *menu = data_ov001_020a04d0.menu;
    FieldMenuEntry *entry = CycleMenuEntry(menu, menu->cursorIndex, 1, NULL);

    if (menu->active == 0) {
        return FALSE;
    }
    if (menu->state != 0) {
        return FALSE;
    }
    if (!IsModeSetOrFlag370aClear()) {
        return FALSE;
    }
    if (IsLeadEntryFlag80Set()) {
        return FALSE;
    }
    switch (data_0205fe0c->menuMode) {
    case 0:
        if (menu->entryCount < 2) {
            return FALSE;
        }
        if (!IsModeSetOrFlag370aClear() || IsHudFlag7Set() || IsFieldFlag10Set()) {
            return FALSE;
        }
        func_ov001_02075d74(menu, TRUE);
        menu->state = TRUE;
        menu->transition = 2;
        menu->timer = 0;
        return TRUE;
    case 2:
    default:
        func_ov001_02075d74(menu, TRUE);
        menu->state = TRUE;
        menu->transition = 0;
        menu->timer = 0;
        return FALSE;
    case 1:
        switch (menu->subMode) {
        case 0:
            return FALSE;
        case 1:
            if (entry->enabled == 0) {
                return FALSE;
            }
            break;
        }
        menu->pendingConfirm = 1;
        return func_ov001_02077ef4();
    }
}
