#include "nitro/types.h"

typedef struct {
    u8 pad[0x54];
    int primaryA;
    int primaryB;
    int secondaryA;
    int secondaryB;
    s16 primaryId;
    s16 secondaryId;
} Slots;

typedef struct {
    u8 pad[8];
    Slots *slots;
    u8 padc[4];
    void *resource;
} Owner;

extern void ReleaseResourceAndDetach(void *resource);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void ReleaseOwnerResource(Owner *owner) {
    Slots *slots = owner->slots;
    if (slots->primaryId >= 0) {
        slots->primaryA = 0;
        slots->primaryB = 0;
    }
    if (owner->resource != NULL) {
        ReleaseResourceAndDetach(owner->resource);
        NNSi_FndFreeFromDefaultHeap(owner->resource);
        owner->resource = NULL;
    }
    if (slots->secondaryId >= 0) {
        slots->secondaryA = 0;
        slots->secondaryB = 0;
    }
}
