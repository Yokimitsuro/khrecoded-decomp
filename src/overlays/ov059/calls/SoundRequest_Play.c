#include "nitro/types.h"

typedef struct {
    s32 kind;
} SoundRequest;

extern u32 SpawnSoundSlot(u32 owner, u32 kind, void *position, u32 flags);

void SoundRequest_Play(SoundRequest *request, void *position)
{
    switch (request->kind) {
    case 1:
        SpawnSoundSlot(0x19d, 2, position, 0);
        break;
    case 2:
        SpawnSoundSlot(0x19d, 3, position, 0);
        break;
    case 3:
        SpawnSoundSlot(0xca, 1, position, 0);
        break;
    case 4:
        SpawnSoundSlot(0xcb, 1, position, 0);
        break;
    }
}
