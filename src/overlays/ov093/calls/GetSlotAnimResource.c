#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u8 body[1];
} AnimResource;

typedef struct {
    u8 pad_00[0x30];
    AnimResource *resource;
    u8 pad_34[0x58];
} AnimElement;

typedef struct {
    u8 pad_0000[0x18];
    AnimElement elements[0x80];
    u8 pad_4618[0x6434 - 0x4618];
} AnimSet;

typedef struct {
    int animIndex;
    u8 pad_04[0x18];
} SlotEntry;

typedef struct {
    u8 pad_0000[0x200];
    AnimSet animSets[2];
    SlotEntry leftSlots[13];
    SlotEntry rightSlots[13];
} SceneWork;

void *GetSlotAnimResource(int side, int slotIndex, SceneWork *work)
{
    AnimSet *set = &work->animSets[side];
    SlotEntry *entry = side == 0 ? &work->leftSlots[slotIndex] : &work->rightSlots[slotIndex];
    int index = entry->animIndex;
    AnimElement *element;
    void *body;

    if (index < 0) {
        return NULL;
    }
    element = &set->elements[index];
    if (element == NULL) {
        return NULL;
    }
    if (element->resource == NULL) {
        return NULL;
    }
    body = element->resource->body;
    if (body == NULL) {
        return NULL;
    }
    return body;
}
