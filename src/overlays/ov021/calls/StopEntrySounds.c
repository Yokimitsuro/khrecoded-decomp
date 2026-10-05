#include "nitro/types.h"

typedef struct SoundOwner {
    int kind;
    u8 pad4[0x74];
    s16 *loopEmitter;
    s16 *voiceEmitter;
    s8 loopHandle;
    s8 voiceHandle;
} SoundOwner;

typedef struct SoundEntry {
    u8 pad0[0x9ac];
    u64 flags;
} SoundEntry;

typedef struct SoundSource {
    u8 pad0[0x14];
    int entryId;
} SoundSource;

extern SoundEntry *GetBoundedEntryField(int id);
extern void StopAndClearSoundEmitter(int emitter, int handle);

void StopEntrySounds(SoundSource *source, SoundOwner *owner)
{
    SoundEntry *entry = GetBoundedEntryField(source->entryId);

    if (owner->loopHandle != -1 && owner->loopEmitter != NULL) {
        StopAndClearSoundEmitter(*owner->loopEmitter, owner->loopHandle);
        owner->loopHandle = -1;
    }
    if (owner->voiceHandle != -1 && owner->voiceEmitter != NULL) {
        if (owner->kind != 0x8d) {
            StopAndClearSoundEmitter(*owner->voiceEmitter, owner->voiceHandle);
        }
        owner->voiceHandle = -1;
    }
    entry->flags |= 0x40;
}
