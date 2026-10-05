#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    s32 id;
    u8 pad_0c[0x3c - 0x0c];
} FieldMenuEntry;

typedef struct {
    u8 pad_000[0xac];
    FieldMenuEntry *entries;
    FieldMenuEntry *shortcuts;
    u8 pad_0b4[0xcc - 0xb4];
    s32 fullCount;
    s32 compactCount;
} FieldMenu;

extern BOOL IsModeSetOrFlag370aClear(void);
extern BOOL IsHudFlag7Set(void);
extern BOOL IsFieldFlag10Set(void);

FieldMenuEntry *FindFieldMenuEntryById(FieldMenu *menu, int list, s32 id, int *outIndex) {
    int index = 0;
    FieldMenuEntry *entry = NULL;
    int i;

    switch (list) {
    case 0:
        if (!IsModeSetOrFlag370aClear() || IsHudFlag7Set() || IsFieldFlag10Set()) {
            for (i = 0; i < menu->fullCount; i++) {
                entry = &menu->entries[i];
                if (entry->id == id) {
                    index = i;
                    break;
                }
            }
        } else {
            for (i = 0; i < menu->compactCount; i++) {
                entry = &menu->entries[i];
                if (entry->id == id) {
                    index = i;
                    break;
                }
            }
        }
        break;
    case 1:
        for (i = 0; i < 14; i++) {
            entry = &menu->shortcuts[i];
            if (entry->id == id) {
                index = i;
                break;
            }
        }
        break;
    case 2:
        break;
    }
    if (outIndex != NULL) {
        *outIndex = index;
    }
    return entry;
}
