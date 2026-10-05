#include "nitro/types.h"

typedef struct EntryInfo {
    u16 unk_0;
    u16 count;
} EntryInfo;

typedef struct ManagerEntry {
    u8 pad_000[0x1d4];
    EntryInfo *info;
} ManagerEntry;

typedef struct FieldFlags {
    u8 pad_00[0x76];
    u8 lowFlags : 4;
    u8 refreshPending : 1;
    u8 highFlags : 3;
} FieldFlags;

typedef struct FieldState {
    u8 pad_0000[0x2740];
    FieldFlags flags;
} FieldState;

extern FieldState *data_ov001_020a0480;
extern ManagerEntry *GetBoundedEntryField(int index);
extern void SetClampedCursor(ManagerEntry *entry, int mode);

void FlushPendingEntryRefresh(void)
{
    FieldState *field = data_ov001_020a0480;
    FieldFlags *flags = &field->flags;

    if (flags->refreshPending) {
        ManagerEntry *entry = GetBoundedEntryField(0);

        if (entry != NULL && entry->info->count == 0) {
            SetClampedCursor(entry, 1);
        }
        flags->refreshPending = FALSE;
    }
}
