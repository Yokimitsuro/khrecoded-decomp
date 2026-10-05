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
    int selected;
    u8 pad[0x110a4 - 4];
    GridTable table;
} GridWork;

extern GridCell *GetGridCell(int column, int row, GridWork *work);
extern void SetGridEntryPosition(int layer, int index, int x, int y, GridWork *work);

BOOL SelectPreviousGridCell(GridWork *work) {
    GridTable *table = &work->table;
    GridCell *cell;
    int startRow;
    int column;
    int row;

    startRow = table->cursor / table->width;
    cell = GetGridCell(table->cursor % table->width, startRow, work);

    while (TRUE) {
        if (--table->cursor < 0) {
            table->cursor = table->width;
            continue;
        }
        column = table->cursor % table->width;
        row = table->cursor / table->width;
        cell = GetGridCell(column, row, work);
        if (cell == NULL) {
            continue;
        }
        if (row == startRow) {
            break;
        }
        column = table->width - 1;
        table->cursor = table->width * startRow + column;
        row = startRow;
        cell = GetGridCell(column, startRow, work);
        if (cell != NULL) {
            break;
        }
    }
    SetGridEntryPosition(0, 3, cell->x, cell->y - table->scroll, work);
    table->cursor = table->width * row + column;
    work->selected = cell->value;
    return TRUE;
}