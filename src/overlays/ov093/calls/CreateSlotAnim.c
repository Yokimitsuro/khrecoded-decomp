#include "nitro/types.h"

typedef struct {
    u32 archive;
    u32 resource;
} AnimSource;

typedef struct {
    AnimSource source;
    int x;
    int y;
    int mode;
    int flag;
    int start;
} SlotAnimDesc;

typedef struct {
    s16 right;
    s16 bottom;
    s16 left;
    s16 top;
} AnimBounds;

typedef struct {
    int animIndex;
    int x;
    int y;
    int width;
    int height;
    AnimBounds bounds;
} SlotEntry;

typedef struct {
    u8 pad_0000[0x200];
    u8 animSets[2][0x6434];
    SlotEntry leftSlots[13];
    SlotEntry rightSlots[13];
} SceneWork;

extern int PXI_Init_0204f0c8(void *animSet, AnimSource source);
extern void func_0204f218(void *animSet, int index, int frame);
extern void IndexedRecord_ClearActive(void *animSet, int index);
extern void Slot_SetMode2Bit(void *animSet, int index, int value);
extern void IndexedRecords_SetFlag2(void *animSet, int index, int value);
extern int IndexedRecord_SetActive(void *animSet, int index);
extern void SetSlotPosition(int side, int slotIndex, int x, int y, SceneWork *work);
extern AnimBounds *GetSlotAnimResource(int side, int slotIndex, SceneWork *work);
extern void MI_CpuCopy8(const void *src, void *dest, int size);

void CreateSlotAnim(int side, int slotIndex, SlotAnimDesc *desc, SceneWork *work)
{
    int offset = side * 0x6434;
    u8 *animSets = work->animSets[0];
    SlotEntry *entry = side == 0 ? &work->leftSlots[slotIndex] : &work->rightSlots[slotIndex];
    int animIndex;
    AnimBounds *bounds;

    animIndex = PXI_Init_0204f0c8(animSets + offset, desc->source);
    func_0204f218(animSets + offset, animIndex, 0);
    IndexedRecord_ClearActive(animSets + offset, animIndex);
    Slot_SetMode2Bit(animSets + offset, animIndex, desc->mode);
    IndexedRecords_SetFlag2(animSets + offset, animIndex, desc->flag);
    if (desc->start != 0) {
        IndexedRecord_SetActive(animSets + offset, animIndex);
    }
    entry->animIndex = animIndex;
    entry->x = desc->x;
    entry->y = desc->y;
    SetSlotPosition(side, slotIndex, desc->x, desc->y, work);
    bounds = GetSlotAnimResource(side, slotIndex, work);
    entry->width = bounds->right - bounds->left + 1;
    entry->height = bounds->bottom - bounds->top + 1;
    MI_CpuCopy8(bounds, &entry->bounds, sizeof(AnimBounds));
}
