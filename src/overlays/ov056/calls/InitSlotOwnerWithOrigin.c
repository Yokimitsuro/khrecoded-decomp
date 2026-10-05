#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotDesc {
    u8 pad_00[4];
    u8 group;
    u8 variant;
    u8 pad_06[2];
    int duration;
} SlotDesc;

typedef struct EntryInfo {
    u8 pad_000[0xbc];
    VecFx32 position;
} EntryInfo;

typedef struct EffectSlotOwner {
    u8 pad_000[0x3c];
    s8 entryIndex;
    u8 pad_03d[3];
    s8 flags;
    u8 pad_041[0xe8 - 0x41];
    VecFx32 origin;
    u8 pad_0f4[0x19c - 0xf4];
    int elapsed;
    u32 fileIndex;
    int group;
    int variant;
    int duration;
    int phase;
} EffectSlotOwner;

extern void func_ov021_020aed44(VecFx32 *out, EffectSlotOwner *owner, u32 fileIndex);
extern EntryInfo *GetBoundedEntryField(int index);

void InitSlotOwnerWithOrigin(EffectSlotOwner *owner, u32 fileIndex, SlotDesc *desc)
{
    VecFx32 offset;
    owner->flags = 0;
    owner->elapsed = 0;
    owner->fileIndex = fileIndex;
    owner->group = desc->group;
    owner->variant = desc->variant;
    owner->duration = desc->duration;
    owner->phase = 1;
    owner->flags |= 2;
    func_ov021_020aed44(&offset, owner, fileIndex);
    owner->origin = GetBoundedEntryField(owner->entryIndex)->position;
}
