#include "nitro/types.h"

typedef struct {
    u8 pad[0x180];
    u8 layers[2][0x6434];
} GridWork;

extern int *GetGridEntry(int layer, int index, GridWork *work);
extern void IndexedRecords_SetFlag2(void *base, int index, int value);

void SetGridEntryVisible(int layer, int index, int visible, GridWork *work) {
    int *entry = GetGridEntry(layer, index, work);
    IndexedRecords_SetFlag2(work->layers[layer], *entry, visible);
}