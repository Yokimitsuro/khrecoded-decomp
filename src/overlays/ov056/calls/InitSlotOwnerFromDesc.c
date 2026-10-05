#include "nitro/types.h"

typedef struct SlotDesc {
    u8 pad_00[4];
    u8 group;
    u8 variant;
    u8 pad_06[2];
    int duration;
} SlotDesc;

typedef struct SlotTiming {
    u32 elapsed : 16;
    u32 phase : 16;
} SlotTiming;

typedef struct EffectSlotOwner {
    u8 pad_000[0x40];
    u8 active;
    u8 pad_041[0x1a0 - 0x41];
    int group;
    int variant;
    int duration;
    u8 pad_1ac[4];
    SlotTiming timing;
} EffectSlotOwner;

void InitSlotOwnerFromDesc(EffectSlotOwner *owner, u32 unused, SlotDesc *desc)
{
    owner->active = 0;
    owner->group = desc->group;
    owner->variant = desc->variant;
    owner->duration = desc->duration;
    owner->timing.elapsed = 0;
    owner->timing.phase = 1;
}
