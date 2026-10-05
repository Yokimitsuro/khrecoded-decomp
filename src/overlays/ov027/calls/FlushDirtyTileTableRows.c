#include "nitro/types.h"

typedef struct TileTable {
    int *ids;
    int count;
    u16 width;
    u16 height;
    u16 rowLength;
    u8 pad_0E[2];
    u16 *rows;
    int loadImmediately;
    u8 dirtyMask;
    u8 pad_19[3];
} TileTable;

typedef int (*TileLoadFunc)(int id, int offset, void *src, int size);

extern int LoadBgScreenData(int id, int offset, void *src, int size);
extern int NNS_GfdRegisterNewVramTransferTask(int id, int offset, void *src, int size);

void FlushDirtyTileTableRows(TileTable *table)
{
    int i;
    int size = table->width * table->height * 2;
    TileLoadFunc load = LoadBgScreenData;

    if (table->loadImmediately == 0) {
        load = NNS_GfdRegisterNewVramTransferTask;
    }
    for (i = 0; i < table->count; i++) {
        if (table->dirtyMask & (1 << i)) {
            load(table->ids[i], 0, &table->rows[table->rowLength * i], size);
        }
    }
    table->dirtyMask = 0;
}

