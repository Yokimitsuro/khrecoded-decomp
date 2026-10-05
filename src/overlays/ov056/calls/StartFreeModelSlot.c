#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ModelSlot {
    u8 pad_000[0xa4];
    VecFx32 position;
    u8 pad_0b0[0x10c - 0xb0];
    u8 tracks[0x130 - 0x10c];
    int active;
} ModelSlot;

typedef struct ModelSlotList {
    ModelSlot *slots;
    s8 count;
} ModelSlotList;

extern void RebindAnimTracks_020aef84(ModelSlot *slot, void *tracks, int blendIndex);

void StartFreeModelSlot(ModelSlotList *list, int blendIndex, VecFx32 *position)
{
    ModelSlot *slot = NULL;
    int i;
    for (i = 0; i < list->count; i++) {
        if (list->slots[i].active == 0) {
            slot = &list->slots[i];
            break;
        }
    }
    if (slot != NULL) {
        RebindAnimTracks_020aef84(slot, slot->tracks, blendIndex);
        slot->position = *position;
        slot->active = 1;
    }
}
