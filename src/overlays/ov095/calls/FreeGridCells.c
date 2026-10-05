#include "nitro/types.h"

typedef struct {
    u8 pad[0x20];
    void **cells;
    int width;
    int height;
    int count;
} GridTable;

typedef struct {
    u8 pad[0x110a4];
    GridTable table;
} GridWork;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeGridCells(GridWork *work) {
    GridTable *table = &work->table;
    int i;

    if (table->cells == NULL) {
        return;
    }
    for (i = 0; i < table->count; i++) {
        if (table->cells[i] != NULL) {
            NNSi_FndFreeFromDefaultHeap(table->cells[i]);
            table->cells[i] = NULL;
        }
    }
    NNSi_FndFreeFromDefaultHeap(table->cells);
    table->cells = NULL;
}