#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s8 inUse;
    s8 actorId;
    s8 anchorMode;
    u8 pad_03;
    u16 flags;
    u8 pad_06[2];
    u8 tracks[0x10c];
    u32 soundHandle;
    u8 pad_118[0x20];
} EntrySlot;

typedef struct {
    EntrySlot *slots;
    s32 slotCount;
} EntryGroup;

extern BOOL data_ov021_020b5628;
extern EntryGroup *func_ov021_020a8830(int groupId);
extern int *func_01ffb2f8(void *state, int track, int frame);
extern void ResolveEntryAnchorPosition(VecFx32 *out, EntrySlot *slot);
extern int func_ov001_02063a38(void);
extern u32 SpawnSoundSlot(u32 owner, u32 kind, VecFx32 *position, u16 flags);

void RestartEntrySlot(int groupId, int index, int soundOwner, int soundKind)
{
    EntryGroup *group;
    EntrySlot *slot;
    VecFx32 anchor;
    VecFx32 position;
    int flags;

    func_ov021_020a8830(groupId);
    if (data_ov021_020b5628 == 0) {
        return;
    }
    group = func_ov021_020a8830(groupId);
    if (group == NULL) {
        return;
    }
    slot = &group->slots[index];
    if (slot->inUse == 1) {
        func_01ffb2f8(slot->tracks, 0, 0);
        func_01ffb2f8(slot->tracks, 1, 0);
        func_01ffb2f8(slot->tracks, 2, 0);
        func_01ffb2f8(slot->tracks, 4, 0);
        func_01ffb2f8(slot->tracks, 3, 0);
    }
    if (soundOwner == -1 || soundKind == -1) {
        return;
    }
    ResolveEntryAnchorPosition(&position, slot);
    anchor = position;
    flags = 0;
    if (func_ov001_02063a38() != 4 && slot->anchorMode != 0) {
        flags |= 5;
    }
    slot->soundHandle = SpawnSoundSlot(soundOwner, soundKind, &anchor, flags);
}
