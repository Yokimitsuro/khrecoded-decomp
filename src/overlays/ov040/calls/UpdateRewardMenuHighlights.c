#include "nitro/types.h"

typedef struct {
    int kind;
    int state;
} MenuEntry;

typedef struct {
    MenuEntry **entries;
    int count;
} MenuEntryList;

typedef struct FieldMenu FieldMenu;
struct FieldMenu {
    u8 pad_000[0x1dc];
    int mode;
    u8 pad_1e0[0x4c];
    int (*getMode)(FieldMenu *menu);
    u8 pad_230[0x784];
    u8 selectionIndex;
    u8 pad_9b5[0x6bb];
    MenuEntryList list;
};

typedef struct {
    u8 pad_00[0xc];
    void *pendingItem;
    s32 timer;
} RewardPopup;

typedef struct {
    u8 pad_00[0x100];
    s32 slotCount;
    s16 cursor;
} SelectionList;

typedef struct {
    u8 pad_00[0x2c];
    SelectionList list;
} SelectionRecord;

extern RewardPopup *data_ov040_020be284;
extern void func_ov007_020a1b28(void *item, u32 *code, u32 *extra);
extern u32 func_ov040_020bdc44(u32 code);
extern void func_ov001_020788b8(u32 id, int arg);
extern int func_ov001_02078494(void);
extern s16 *GetPlayerFlagRecord(int index);
extern SelectionRecord *GetOverlaySelectionRecord(u32 index);
extern void SetMenuEntryHighlight(int listKind, int entryId, BOOL highlighted);

void UpdateRewardMenuHighlights(FieldMenu *menu) {
    MenuEntryList *list = &menu->list;
    BOOL enabled = TRUE;
    RewardPopup *popup = data_ov040_020be284;
    int mode;
    int i;
    int count;
    s16 extra;
    SelectionList *selection;

    if (popup->pendingItem != NULL) {
        popup->timer += 0x1000;
        if (popup->timer > 0xf000) {
            u32 code;
            u32 detail;
            func_ov007_020a1b28(popup->pendingItem, &code, &detail);
            func_ov001_020788b8(func_ov040_020bdc44(code), 0);
            popup->pendingItem = NULL;
        }
    }
    if (menu->getMode != NULL) {
        mode = menu->getMode(menu);
    } else {
        mode = menu->mode;
    }
    if (mode == 8) {
        enabled = FALSE;
    }
    switch (func_ov001_02078494()) {
    case 1:
        for (i = 0; i < 8; i++) {
            switch (*GetPlayerFlagRecord(i)) {
            case -1:
                break;
            case 0xd0:
            case 0xd1:
            case 0xd2:
                SetMenuEntryHighlight(1, i, enabled);
                break;
            default:
                SetMenuEntryHighlight(1, i, FALSE);
                break;
            }
        }
        break;
    case 0:
        selection = &GetOverlaySelectionRecord(menu->selectionIndex)->list;
        extra = selection->cursor;
        count = list->count;
        if (extra != -1) {
            count--;
        }
        for (i = 0; i < count; i++) {
            MenuEntry *entry = list->entries[i];
            if (entry != NULL) {
                switch (entry->kind) {
                case 0xa0:
                case 0xa1:
                case 0xa2:
                    SetMenuEntryHighlight(0, i, enabled);
                    break;
                default:
                    if (entry->state == 1) {
                        SetMenuEntryHighlight(0, i, enabled);
                    }
                    break;
                }
            } else {
                SetMenuEntryHighlight(0, i, FALSE);
            }
        }
        break;
    }
}
