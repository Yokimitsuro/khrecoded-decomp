#include "nitro/types.h"

typedef struct TileTable {
    int *ids;
    int count;
} TileTable;

int FindTileTableIndex(TileTable *table, int id)
{
    int i;
    int result = -1;

    for (i = 0; i < table->count; i++) {
        if (id == table->ids[i]) {
            result = i;
            break;
        }
    }
    return result;
}
