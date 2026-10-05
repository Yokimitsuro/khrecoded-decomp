#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

extern s16 PXI_Init_0204f0c8(ResourceContainer *container, int cellId, int flags);
extern void IndexedRecord_ClearActive(ResourceContainer *container, int cellIndex);

void CreateContainerCells(ResourceContainer *container, s16 *cells, int cellId, int count)
{
    int i = 0;

    do {
        *cells = PXI_Init_0204f0c8(container, cellId, 0);
        IndexedRecord_ClearActive(container, *cells);
        cells++;
    } while (++i < count);
}
