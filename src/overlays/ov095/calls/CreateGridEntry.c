#include "nitro/types.h"

typedef struct {
    int spriteId;
    int x;
    int y;
    int visible;
    int mode2;
} GridEntryDesc;

typedef struct {
    int spriteIndex;
    int x;
    int y;
    int width;
    int height;
} GridEntry;

typedef struct {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} SpriteBounds;

typedef struct {
    u8 pad[0x180];
    u8 layers[2][0x6434];
} GridWork;

extern GridEntry *GetGridEntry(int layer, int index, GridWork *work);
extern int PXI_Init_0204f0c8(void *base, int spriteId, int arg);
extern void func_0204f218(void *base, int index, int arg);
extern int IndexedRecord_SetActive(void *base, int index);
extern void Slot_SetMode2Bit(void *base, int index, int value);
extern void IndexedRecords_SetFlag2(void *base, int index, int value);
extern void SetGridEntryPosition(int layer, int index, int x, int y, GridWork *work);
extern SpriteBounds *GetGridEntrySpriteData(int layer, int index, GridWork *work);

void CreateGridEntry(int layer, int index, GridEntryDesc *desc, GridWork *work) {
    u8 *layerBase = work->layers[layer];
    GridEntry *entry = GetGridEntry(layer, index, work);
    int sprite;
    SpriteBounds *bounds;

    sprite = PXI_Init_0204f0c8(layerBase, desc->spriteId, 0);
    func_0204f218(layerBase, sprite, 0);
    IndexedRecord_SetActive(layerBase, sprite);
    Slot_SetMode2Bit(layerBase, sprite, desc->mode2);
    IndexedRecords_SetFlag2(layerBase, sprite, desc->visible);
    entry->spriteIndex = sprite;
    entry->x = desc->x;
    entry->y = desc->y;
    SetGridEntryPosition(layer, index, desc->x, desc->y, work);
    bounds = GetGridEntrySpriteData(layer, index, work);
    entry->width = bounds->left - bounds->right + 1;
    entry->height = bounds->top - bounds->bottom + 1;
}