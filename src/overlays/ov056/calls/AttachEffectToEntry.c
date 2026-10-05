#include "nitro/types.h"

typedef struct SlotDesc {
    u8 pad_00[4];
    u8 group;
    u8 variant;
    u8 pad_06[2];
    int duration;
} SlotDesc;

typedef struct LinkedEntry LinkedEntry;
typedef void (*PlayAnimationFunc)(LinkedEntry *entry, int animation, int arg2, int arg3);
struct LinkedEntry {
    u8 pad_000[0x1f0];
    PlayAnimationFunc playAnimation;
    u8 pad_1f4[0x6fc - 0x1f4];
    u8 attachPoint[4];
};

typedef struct AttachedEffect {
    u8 pad_000[0x3c];
    s8 entryIndex;
    u8 pad_03d[3];
    s8 flags;
    u8 pad_041[3];
    u8 tracks[0x150 - 0x44];
    u8 blendTable[0x188 - 0x150];
    s16 animation;
    u8 pad_18a[0x190 - 0x18a];
    void *attachPoint;
    int phase;
    int elapsed;
    int group;
    int variant;
    int duration;
} AttachedEffect;

extern LinkedEntry *GetBoundedEntryField(int index);
extern void RebindAnimTracks_020aef84(void *tracks, void *blendTable, int blendIndex);

void AttachEffectToEntry(AttachedEffect *effect, u32 unused, SlotDesc *desc)
{
    int animation;
    LinkedEntry *entry = GetBoundedEntryField(effect->entryIndex);
    effect->flags = 0;
    RebindAnimTracks_020aef84(effect->tracks, effect->blendTable, 0);
    effect->flags |= 1;
    animation = effect->animation;
    if (entry->playAnimation != NULL) {
        entry->playAnimation(entry, animation, 0, 0);
    }
    effect->elapsed = 0;
    effect->phase = 1;
    effect->group = desc->group;
    effect->variant = desc->variant;
    effect->duration = desc->duration;
    effect->attachPoint = entry->attachPoint;
}
