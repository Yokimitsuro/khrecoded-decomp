#include "nitro/types.h"

typedef struct {
    int x;
    int y;
} GridPoint;

typedef struct {
    int id;
    GridPoint pos;
    u8 rest[8];
} TabLayout;

typedef struct {
    u8 pad[0x34];
    int scroll;
} GridTable;

typedef struct {
    u8 pad[0x110a4];
    GridTable table;
} GridWork;

extern TabLayout data_ov095_020c18b4[];
extern BOOL IsEntryFlagSet_020c1340(int useSecondSet, int bitIndex);
extern void SetGridEntryPosition(int layer, int index, int x, int y, GridWork *work);
extern void SetGridEntryVisible(int layer, int index, int visible, GridWork *work);

void LayoutTabEntries(GridWork *work) {
    GridTable *table = &work->table;
    int i;

    for (i = 4; i <= 12; i++) {
        BOOL unlocked = IsEntryFlagSet_020c1340(1, i - 4);
        GridPoint pos = data_ov095_020c18b4[i].pos;
        pos.y -= table->scroll;
        SetGridEntryPosition(0, i, pos.x, pos.y, work);
        SetGridEntryVisible(0, i, unlocked, work);
    }
}