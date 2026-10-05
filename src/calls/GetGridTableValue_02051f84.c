#include "nitro/types.h"

typedef struct GridTable {
    int rowStart[10];
    int values[1];
} GridTable;

typedef struct GridTables {
    u8 pad_00[0x20];
    GridTable *table;
} GridTables;

extern GridTables *data_020613d0;

int GetGridTableValue_02051f84(int row, int column)
{
    GridTables *tables = data_020613d0;
    GridTable *table = tables->table;
    int index;

    if (tables == NULL || table == NULL) {
        return 0;
    }
    if (column >= 0) {
        index = table->rowStart[row] + column;
    } else {
        index = row;
    }
    return table->values[index];
}
