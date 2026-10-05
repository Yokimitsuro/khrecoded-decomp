#include "nitro/types.h"
#include "nitro/fx_types.h"

#define INT_TO_FX32(n) ((fx32)((float)(n) > 0 ? 0.5f + 4096.0f * (float)(n) : 4096.0f * (float)(n) - 0.5f))

typedef struct {
    fx32 x;
    fx32 y;
} PointFx32;

typedef struct {
    int animIndex;
    int x;
    int y;
    u8 pad_0c[0x10];
} SlotEntry;

typedef struct {
    u8 pad_0000[0x200];
    u8 animSets[2][0x6434];
    SlotEntry leftSlots[13];
    SlotEntry rightSlots[13];
} SceneWork;

extern void IndexedRecord_SetPair(void *animSet, int index, PointFx32 *position);

void SetSlotPosition(int side, int slotIndex, int x, int y, SceneWork *work)
{
    int offset = side * 0x6434;
    u8 *animSets = work->animSets[0];
    SlotEntry *entry = side == 0 ? &work->leftSlots[slotIndex] : &work->rightSlots[slotIndex];
    PointFx32 position;

    entry->x = x;
    entry->y = y;
    position.x = INT_TO_FX32(entry->x);
    position.y = INT_TO_FX32(entry->y);
    IndexedRecord_SetPair(animSets + offset, entry->animIndex, &position);
}
