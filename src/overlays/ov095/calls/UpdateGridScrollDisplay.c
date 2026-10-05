#include "nitro/types.h"

typedef struct {
    int value;
    int x;
    int y;
} GridCell;

typedef struct {
    u8 pad[0x24];
    int width;
    int height;
    int count;
    int cursor;
    int scroll;
} GridTable;

typedef struct {
    u8 pad0[0x110a4];
    GridTable table;
    u8 pad1[0x11108 - 0x110a4 - sizeof(GridTable)];
    int refreshPending;
    u8 pad2[0x11120 - 0x1110c];
    int hasSelection;
} GridWork;

extern GridCell *GetGridCell(int column, int row, GridWork *work);
extern BOOL IsEntryFlagSet_020c1340(int useSecondSet, int bitIndex);
extern void func_ov095_020bfa38(int mode, GridWork *work);
extern void SetPanelMode_020c1210(int mode, GridWork *work);

#define REG_BG3OFS (*(vu32 *)0x0400001c)
#define REG_DB_DISPCNT (*(vu32 *)0x04001000)

void UpdateGridScrollDisplay(GridWork *work) {
    u32 planes;

    REG_BG3OFS = ((work->table.scroll - 0x20) << 16) & 0x1ff0000;
    planes = (REG_DB_DISPCNT & 0x1f00) >> 8;
    if (work->hasSelection == 0) {
        if (work->refreshPending == 1) {
            work->refreshPending = 0;
            func_ov095_020bfa38(1, work);
        }
        planes &= ~4;
    } else {
        GridTable *table = &work->table;
        GridCell *cell = GetGridCell(table->cursor % table->width, table->cursor / table->width, work);
        if (IsEntryFlagSet_020c1340(0, cell->value)) {
            planes |= 4;
        } else {
            planes &= ~4;
        }
    }
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | (planes << 8);
    SetPanelMode_020c1210(0, work);
}