#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    int spriteIndex;
    int x;
    int y;
} GridEntry;

typedef struct {
    u8 pad[0x180];
    u8 layers[2][0x6434];
} GridWork;

typedef struct {
    fx32 x;
    fx32 y;
} GridPosFx;

extern GridEntry *GetGridEntry(int layer, int index, GridWork *work);
extern void IndexedRecord_SetPair(void *base, int index, GridPosFx *pos);

#define INT_TO_FX32_ROUNDED(v) ((fx32)((float)(v) > 0.0f ? 0.5f + 4096.0f * (float)(v) : 4096.0f * (float)(v) - 0.5f))

void SetGridEntryPosition(int layer, int index, int x, int y, GridWork *work) {
    u8 *layerBase = work->layers[layer];
    GridEntry *entry = GetGridEntry(layer, index, work);
    GridPosFx pos;

    entry->x = x;
    entry->y = y;
    pos.x = INT_TO_FX32_ROUNDED(entry->x);
    pos.y = INT_TO_FX32_ROUNDED(entry->y);
    IndexedRecord_SetPair(layerBase, entry->spriteIndex, &pos);
}