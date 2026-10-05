#include "nitro/types.h"

typedef struct MenuEntry {
    u8 pad_000[0x1dc];
    int state;
    u8 pad_1e0[0x21c - 0x1e0];
    u32 (*getFlags)(struct MenuEntry *entry);
    u8 pad_220[0x22c - 0x220];
    int (*getState)(struct MenuEntry *entry);
} MenuEntry;

typedef struct MenuOwner {
    u8 pad_000[0x1dc];
    int state;
    u8 pad_1e0[0x22c - 0x1e0];
    int (*getState)(struct MenuOwner *owner);
    u8 pad_230[0x9ac - 0x230];
    u64 flags;
    u8 selection;
    u8 pad_9b5[0x9ec - 0x9b5];
    int animHandle;
} MenuOwner;

typedef struct SelectionItem {
    s16 id;
    u8 pad_02[10];
} SelectionItem;

typedef struct SelectionList {
    SelectionItem items[0x100 / 12];
    u8 pad_fc[0x100 - 0xfc];
    int count;
} SelectionList;

typedef struct SelectionRecord {
    u8 pad_000[0x2c];
    SelectionList list;
} SelectionRecord;

typedef struct SceneGlobals {
    u8 pad_0000[0x1264];
    int secondEntry;
    int firstEntry;
    int mode;
    int dirty;
} SceneGlobals;

extern SceneGlobals *data_ov054_020d3720;

extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern SelectionRecord *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern unsigned int func_ov001_02064490(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void func_ov001_0206c634(int enableFirst, int enableSecond);
extern MenuEntry *GetBoundedEntryField(int index);
extern void *func_ov001_0206db78(u32 index);
extern BOOL func_ov001_0206e224(void);
extern void SetSceneAnimState(int state);
extern void SetMenuEntryHighlight(int listKind, int entryId, BOOL highlighted);
extern BOOL IsMenuItemAssigned_02078a3c(int itemId);
extern BOOL IsMenuItemLinked(int itemId);
extern unsigned short SharedObject_GetId(void *self);
extern void func_ov058_020d81c4(int handle);
extern void SetEnemyTargetAndClearFlag(MenuEntry *entry, int mode);

void RefreshModeMenuHighlights(MenuOwner *owner)
{
    SceneGlobals *globals = data_ov054_020d3720;
    BOOL secondLocked = FALSE;
    BOOL firstLocked = FALSE;
    int animState = -1;
    BOOL enabled = TRUE;
    MenuEntry *entry;
    int i;
    int state;
    SelectionList *list;
    BOOL changed;

    switch (globals->mode) {
    case 4:
        animState = 1;
        break;
    case 5:
        animState = 0;
        break;
    case 6:
        animState = 2;
        break;
    }
    SetSceneAnimState(animState);
    func_ov058_020d81c4(owner->animHandle);

    if (func_ov001_020645c8(0x3609) && globals->firstEntry >= 0) {
        u32 flags;
        entry = GetBoundedEntryField(globals->firstEntry);
        if (entry->getFlags == NULL) {
            flags = 0;
        } else {
            flags = entry->getFlags(entry);
        }
        if (!(flags & 2)) {
            firstLocked = TRUE;
        }
    }
    if (func_ov001_020645c8(0x360a) && globals->secondEntry >= 0) {
        u32 flags;
        entry = GetBoundedEntryField(globals->secondEntry);
        if (entry->getFlags == NULL) {
            flags = 0;
        } else {
            flags = entry->getFlags(entry);
        }
        if (!(flags & 2)) {
            secondLocked = TRUE;
        }
    }

    entry = GetBoundedEntryField(owner->selection);
    if (entry->getState == NULL) {
        state = entry->state;
    } else {
        state = entry->getState(entry);
    }
    if (state == 2 || state == 4 || state == 8) {
        enabled = FALSE;
    }

    list = &GetOverlaySelectionRecord(owner->selection)->list;
    for (i = 0; i < list->count; i++) {
        switch (list->items[i].id) {
        case 0xb9:
        case 0xba: {
            BOOL usable = enabled;
            if (!func_ov001_0206e224()) {
                usable = FALSE;
            }
            if (owner->getState == NULL) {
                state = owner->state;
            } else {
                state = owner->getState(owner);
            }
            if (state == 10) {
                usable = FALSE;
            }
            SetMenuEntryHighlight(0, i, usable);
            break;
        }
        case 0xb7:
        case 0xb8:
        case 0xbb:
        case 0xbc:
        case 0xbd:
            SetMenuEntryHighlight(0, i, enabled);
            break;
        default:
            if ((!firstLocked && IsMenuItemAssigned_02078a3c(i))
                || (!secondLocked && IsMenuItemLinked(i))) {
                SetMenuEntryHighlight(0, i, FALSE);
            } else {
                SetMenuEntryHighlight(0, i, enabled);
            }
            break;
        }
    }

    changed = FALSE;
    if (owner->flags & 0x800) {
        return;
    }
    if (func_ov001_02064490()) {
        return;
    }
    if (SharedObject_GetId(func_ov001_0206db78(owner->selection)) == 1) {
        globals->mode++;
        if (globals->mode >= 7) {
            globals->mode = 4;
        }
        PlaySoundEffect(0x1a2, 0);
        changed = TRUE;
    } else if (globals->dirty != 0) {
        changed = TRUE;
    }
    if (!changed) {
        return;
    }
    globals->dirty = 0;
    if (globals->secondEntry > 0) {
        SetEnemyTargetAndClearFlag(GetBoundedEntryField(globals->secondEntry), globals->mode);
    }
    if (globals->firstEntry > 0) {
        SetEnemyTargetAndClearFlag(GetBoundedEntryField(globals->firstEntry), globals->mode);
    }
    {
        int enableFirst = TRUE;
        int enableSecond = TRUE;
        switch (globals->mode) {
        case 5:
            enableSecond = FALSE;
            break;
        case 6:
            enableFirst = FALSE;
            break;
        }
        func_ov001_0206c634(enableFirst, enableSecond);
    }
}
