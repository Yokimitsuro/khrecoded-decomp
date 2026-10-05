#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x3c];
    s8 isHeavy;
    s8 kind;
} SoundSource;

typedef struct {
    u8 pad_00[0x58];
    s16 soundOwner;
} SoundOwnerInfo;

typedef struct {
    u8 pad_00[0x138];
    SoundOwnerInfo *info;
} SoundTarget;

typedef struct {
    u32 pad_00[2];
    u32 type;
    u32 position[3];
} HitEvent;

extern u32 SpawnSoundSlot(u32 owner, u32 kind, u32 *position, u32 flags);

void PlayHitReactionSound(SoundSource *source, SoundTarget *target, HitEvent *event)
{
    SoundOwnerInfo *info = target->info;
    int sound = -1;

    switch (source->kind) {
    default:
        switch (event->type) {
        case 2:
        case 3:
        case 4:
            sound = 1;
            break;
        case 1:
            sound = 2;
            if (source->isHeavy != 0) {
                sound = 1;
            }
            break;
        }
        break;
    case 2:
    case 9:
    case 10:
    case 11:
        sound = 1;
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 0xe:
    case 0xf:
    case 0x11:
        break;
    }    if (sound >= 0) {
        SpawnSoundSlot(info->soundOwner, sound, event->position, 0);
    }
}