#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x54];
    s16 soundOwner;
    s16 soundKind;
} SoundSource;

typedef struct {
    u8 pad_000[0x138];
    SoundSource *source;
} EventOwner;

typedef struct {
    u32 flags;
    u32 unk_04;
    u32 kind;
    VecFx32 position;
} AnimEvent;

extern u32 SpawnSoundSlot(u32 owner, u32 kind, VecFx32 *position, u32 flags);

void OnAnimEventSound(void *context, EventOwner *owner, AnimEvent *event)
{
    SoundSource *source = owner->source;

    switch (event->kind) {
    case 1:
    case 2:
    case 3:
    case 4:
        if (!(event->flags & 0x30) && (source->flags & 0x40) && source->soundOwner >= 0 && source->soundKind >= 0) {
            SpawnSoundSlot(source->soundOwner, source->soundKind, &event->position, 0);
        }
        break;
    }
}
