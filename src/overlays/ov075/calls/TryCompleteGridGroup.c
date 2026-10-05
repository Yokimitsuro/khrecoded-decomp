#include "nitro/types.h"

typedef struct {
    u16 id;
    u8 kind;
    s8 linkedIndex;
} GridEntry;

typedef struct {
    u8 pad_00[4];
    s16 cell;
    u8 pad_06[6];
    s16 neighbors[4];
} GroupNode;

typedef struct {
    u8 pad_0000[0x9c];
    GridEntry *cells[0x850];
    GroupNode *groups[13][16];
    u8 groupCounts[13];
} GridMap;

typedef struct {
    u8 pad_0000[0x2c5c];
    int flags[1];
    u16 completedGroups;
} SaveData;

typedef struct {
    u8 pad_00000[0x12dd0];
    GridMap *map;
} MatrixMenu;

extern SaveData *data_0205fe0c;
extern int GetPackedBitMask(int *bitWords, int bitIndex);

BOOL TryCompleteGridGroup(MatrixMenu *menu, u32 group)
{
    GridMap *map = menu->map;
    GroupNode **nodes = map->groups[group];
    int i;
    int count = map->groupCounts[group];

    for (i = 0; i < count; i++) {
        s16 *neighbor;
        int j = 4;
        GroupNode *node = nodes[i];
        neighbor = node->neighbors;
        if (node->cell < 0) {
            return FALSE;
        }
        for (; j > 0; j--) {
            if (*neighbor >= 0) {
                GridEntry *entry = menu->map->cells[*neighbor];
                if (entry->kind >= 0xe && entry->linkedIndex >= 0 &&
                    !(GetPackedBitMask(data_0205fe0c->flags, entry->linkedIndex) ? TRUE : FALSE)) {
                    return FALSE;
                }
            }
            neighbor++;
        }
    }
    data_0205fe0c->completedGroups |= (u16)(1 << group);
    return TRUE;
}
