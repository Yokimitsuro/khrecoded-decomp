#include "nitro/types.h"

typedef struct FieldMenu FieldMenu;

typedef struct FieldMenuEntry {
    u8 pad_00[0x10];
    int kind;
    u8 pad_14[0x10];
    void *linked;
    u16 flags;
} FieldMenuEntry;

typedef struct FieldMenuHandle {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;
extern FieldMenuEntry *func_ov001_020754d8(FieldMenu *menu, int listKind, int entryId, s32 *outIndex);
extern BOOL IsFieldFlag13OrSessionFlagSet(void);

void SetMenuEntryHighlight(int listKind, int entryId, BOOL highlighted)
{
    FieldMenuEntry *entry = func_ov001_020754d8(data_ov001_020a04d0.menu, listKind, entryId, NULL);

    if (entry == NULL) {
        return;
    }
    if (!IsFieldFlag13OrSessionFlagSet() || entry->kind == 3 || entry->linked != NULL) {
        if (highlighted) {
            entry->flags |= 6;
        } else {
            entry->flags &= 0xfffb;
            entry->flags |= 2;
        }
    }
}
