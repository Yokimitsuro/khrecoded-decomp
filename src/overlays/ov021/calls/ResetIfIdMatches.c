#include "nitro/types.h"

typedef struct IdOwner {
    u8 pad_00[0x20];
    int id;
} IdOwner;

extern void StopCueGroupSounds(IdOwner *owner, int id);

void ResetIfIdMatches(IdOwner *owner, int id)
{
    if (owner->id == id) {
        StopCueGroupSounds(owner, -1);
    }
}
