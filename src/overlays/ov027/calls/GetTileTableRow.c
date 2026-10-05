#include "nitro/types.h"

typedef struct TileTable {
    int *ids;
    int count;
    u8 pad_08[4];
    u16 rowLength;
    u8 pad_0E[2];
    u16 *rows;
} TileTable;

extern int FindTileTableIndex(TileTable *table, int id);

u16 *GetTileTableRow(TileTable *table, int id, int *indexOut)
{
    int index = FindTileTableIndex(table, id);
    u16 *row;

    if (index < 0) {
        return NULL;
    }
    row = &table->rows[table->rowLength * index];
    if (indexOut != NULL) {
        *indexOut = index;
    }
    return row;
}

