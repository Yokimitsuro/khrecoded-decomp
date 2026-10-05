#include "nitro/types.h"

typedef struct {
    u16 id;
    u8 kind;
    s8 linkedIndex;
    u8 pad_04[0x10];
} GridEntry;

typedef struct {
    u8 pad_0000[0x18];
    GridEntry *linked[0x20];
    u8 *columnCount;
    GridEntry *cells[0xad3];
    u8 levels[0x74];
    int flags[2];
} GridMap;

extern GridMap *data_0205fe0c;
extern int GetPackedBitMask(int *bitWords, int bitIndex);

BOOL ResolveGridEntry(int column, int row, GridMap *map, GridEntry **outEntry)
{
    GridEntry *entry;
    int index;

    if (column >= 0 && column < 0x2f && row > 0 && row < 0x23) {
        entry = map->cells[column + row * *map->columnCount];
        if (entry != NULL) {
            if (entry >= map->linked[0]) {
                index = entry - map->linked[0];
            } else {
                index = -1;
            }
            if (index < 0 && entry->linkedIndex != 0) {
                index = entry->linkedIndex;
            }
            if (index >= 0) {
                if (!(GetPackedBitMask(data_0205fe0c->flags, index) ? TRUE : FALSE)) {
                    *outEntry = map->linked[index];
                    goto check;
                }
            } else if (entry->kind < 0xe) {
                *outEntry = entry;
                goto check;
            }
        }
    }
    return FALSE;

check:
    if (map->levels[entry->id] <= data_0205fe0c->levels[0x7f]) {
        return TRUE;
    }
    return FALSE;
}
