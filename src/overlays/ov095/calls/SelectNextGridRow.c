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

BOOL SelectNextGridRow(GridWork *work) {
    GridTable *table = &work->table;
    int startRow = table->cursor / table->width;
    GridCell *cell = GetGridCell(table->cursor % table->width, startRow, work);
    int column;
    int row;

    do {
        table->cursor++;
        column = table->cursor % table->width;
        row = table->cursor / table->width;
        cell = GetGridCell(column, row, work);
    } while (cell == NULL);
    if (row != startRow) {
        row--;
        cell = GetGridCell(column, row, work);
    }
    SetGridEntryPosition(0, 3, cell->x, cell->y - table->scroll, work);
    table->cursor = table->width * row + column;
    work->selected = cell->value;
    return TRUE;
}