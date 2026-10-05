#include "nitro/types.h"

typedef struct RecentRing {
    u8 entries[0x80];
    u16 readIndex;
    u16 writeIndex;
    u8 count;
} RecentRing;

extern u8 *gSoundWork;

RecentRing *RecentRing_Reset(void)
{
    RecentRing *ring = (RecentRing *)(gSoundWork + 0xb4738);
    ring->readIndex = 0;
    ring->writeIndex = 0;
    ring->count = 0;
    return ring;
}
