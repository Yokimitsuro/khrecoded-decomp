#include "nitro/types.h"

typedef struct ManagerEntry {
    u32 unk_00;
    void *object;
    u8 pad_08[0x1c];
    u16 flags;
    u16 unk_26;
} ManagerEntry;

typedef struct FieldManager {
    u32 unk_00;
    ManagerEntry entries[3];
    int entryCount;
} FieldManager;

extern FieldManager *data_ov001_020a04bc;

BOOL IsFirstEntryFlagSet(void)
{
    FieldManager *manager = data_ov001_020a04bc;
    ManagerEntry *entry;
    BOOL result = TRUE;

    if (manager != NULL) {
        entry = &manager->entries[0];
        if (entry != NULL && (entry->flags & 0x10) <= 0) {
            result = FALSE;
        }
    }
    return result;
}
