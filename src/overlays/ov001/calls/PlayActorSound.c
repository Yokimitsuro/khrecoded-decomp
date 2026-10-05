#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SoundSlot {
    u8 flags;
    u8 handleId;
} SoundSlot;

typedef struct SoundActor {
    u8 pad_000[0x2c0];
    VecFx32 position;
    u8 pad_2cc[0x33a - 0x2cc];
    u16 soundNodeId;
    u8 pad_33c[0x3b4 - 0x33c];
    SoundSlot soundSlots[8];
} SoundActor;

typedef struct SoundHandleEntry {
    u16 bank;
    u16 soundId;
    u32 handle;
} SoundHandleEntry;

extern void GetNodePosition(SoundActor *actor, u16 nodeId, VecFx32 *position);
extern void PlayStageSoundAt(u16 bank, u16 soundId, VecFx32 *position, u16 volume);
extern u8 PlayTrackedStageSound(u16 bank, u16 soundId, VecFx32 *position, u16 volume);
extern SoundHandleEntry *GetStageEntrySlot(u32 id);
extern void ReleaseSlotResource(u32 id);

void PlayActorSound(SoundActor *actor, u16 bank, u16 soundId, u32 flags, u16 volume)
{
    VecFx32 position;
    u8 handleId;
    s32 freeSlot;
    SoundSlot *slot;
    int i;
    SoundHandleEntry *entry;

    if (bank == 0 && soundId == 0) {
        return;
    }
    if (bank == 0) {
        if (soundId == 0x25) {
            flags |= 1;
        }
        if (soundId == 0x26) {
            flags |= 1;
        }
        if (soundId == 0x2d) {
            flags |= 1;
        }
    }
    if (actor->soundNodeId != 0) {
        GetNodePosition(actor, actor->soundNodeId, &position);
    } else {
        position = actor->position;
    }
    if (flags & 1) {
        PlayStageSoundAt(bank, soundId, &position, volume);
        return;
    }
    handleId = PlayTrackedStageSound(bank, soundId, &position, volume);
    if (handleId == 0) {
        return;
    }
    freeSlot = -1;
    for (i = 0; i < 8; i++) {
        slot = &actor->soundSlots[i];
        if (slot->handleId == 0) {
            if (freeSlot < 0) {
                slot->handleId = handleId;
                slot->flags = 0;
                if (flags & 4) {
                    slot->flags |= 4;
                }
                freeSlot = 0;
            }
        } else if (flags & 2) {
            entry = GetStageEntrySlot(slot->handleId);
            if (entry != NULL && entry->handle != 0 && entry->bank == bank && entry->soundId == soundId) {
                ReleaseSlotResource(slot->handleId);
            }
        }
    }
}
