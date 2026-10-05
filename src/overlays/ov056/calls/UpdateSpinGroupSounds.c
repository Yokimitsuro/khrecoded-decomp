#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SoundSlot {
    u8 pad_000[0x100];
    u32 handle;
} SoundSlot;

typedef struct SpinEntry {
    u8 pad_000[2];
    s8 state;
    u8 pad_003[0x30 - 3];
    u16 nodeFlags;
    u8 pad_032[0xac - 0x32];
    u16 angle;
    u8 pad_0ae[0xd4 - 0xae];
    VecFx32 position;
    u8 pad_0e0[0x150 - 0xe0];
    SoundSlot *sound;
} SpinEntry;

typedef struct EntryInfo {
    u8 pad_000[0xbc];
    VecFx32 position;
} EntryInfo;

typedef struct SpinGroup {
    u8 pad_000[8];
    SpinEntry *entries;
    u8 pad_00c[0x15 - 0xc];
    u8 count;
    u8 pad_016[0x3c - 0x16];
    s8 entryIndex;
    u8 pad_03d[3];
    s8 flags;
    u8 pad_041[3];
    u16 nodeFlags;
} SpinGroup;

extern u16 Camera_GetDriftHeading(void);
extern EntryInfo *GetBoundedEntryField(int index);
extern BOOL func_0204dc50(u32 handle);
extern void Handle_WritePayloadIfLive(unsigned int handle, VecFx32 *src);
extern void func_ov021_020ae8ac(u16 *node);

void UpdateSpinGroupSounds(SpinGroup *group)
{
    int i;
    for (i = 0; i < group->count; i++) {
        SpinEntry *entry = &group->entries[i];
        if (entry->state != -1) {
            SoundSlot *sound;
            entry->angle = Camera_GetDriftHeading();
            entry->nodeFlags |= 0x20;
            entry->position = GetBoundedEntryField(group->entryIndex)->position;
            sound = entry->sound;
            if (func_0204dc50(sound->handle)) {
                Handle_WritePayloadIfLive(sound->handle, &entry->position);
            } else {
                sound->handle = 0;
            }
            func_ov021_020ae8ac(&entry->nodeFlags);
        }
    }
    if (group->flags & 1) {
        func_ov021_020ae8ac(&group->nodeFlags);
    }
}
