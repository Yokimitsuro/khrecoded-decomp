#include "nitro/types.h"

typedef struct SlotEntry {
    u8 pad_00[0x4];
    s16 id;
    u8 pad_06[0x26];
} SlotEntry;

typedef struct SlotGroup {
    SlotEntry entries[5];
} SlotGroup;

typedef struct SlotTimer {
    s32 value;
    u8 pad_04[0xC];
} SlotTimer;

typedef struct SlotOwner {
    u8 pad_000[0x1C];
    SlotTimer timers[6][2];
} SlotOwner;

typedef struct SlotSystem {
    union {
        SlotOwner owner;
        struct {
            u8 pad_000[0xD0];
            SlotGroup groups[6];
        } table;
    } u;
    u8 pad_5F8[0x8FC];
    u32 flags;
} SlotSystem;

extern BOOL SetupStreamSlot(SlotSystem *system, SlotEntry *entry, s32 arg1, s32 arg2, s32 slot, s32 arg4, s32 arg5);

void ActivateFreeSlotEntry(SlotSystem *system, s32 arg1, s32 arg2, s32 slot, s32 arg4, s32 arg5)
{
    s32 i;
    s32 j;

    for (i = 0; i < 6; i++) {
        SlotEntry *entry = &system->u.table.groups[i].entries[slot];
        if (entry->id == -1 && SetupStreamSlot(system, entry, arg1, arg2, slot, arg4, arg5)) {
            for (j = 0; j < 2; j++) {
                system->u.owner.timers[i][j].value = 0;
            }
            break;
        }
    }
    system->flags |= 0x200;
}
