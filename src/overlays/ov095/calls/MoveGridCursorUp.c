#include "nitro/types.h"

typedef struct {
    int id;
    int unk04;
    int y;
} GridCell;

typedef struct {
    int a;
    int b;
    u8 pad_08[0xc];
} GridSlot;

typedef struct {
    int slot;
    u8 pad_04[0x20];
    int width;
    int rows;
    u8 pad_2c[4];
    int pos;
    int scroll;
    int viewTop;
    u8 pad_3c[4];
    int scrollTimer;
} GridCursor;

typedef struct {
    int selectedId;
    u8 pad_0004[0xc9e8];
    GridSlot slots[1];
} GridScene;

#define GRID_CURSOR(scene) ((GridCursor *)((u8 *)(scene) + 0x110a4))

extern u16 data_02060500;
extern GridCell *GetGridCell(int column, int row, GridScene *owner);
extern void SetGridEntryPosition(int mode, int slot, int a, int b, GridScene *scene);
extern void RefreshCursorMarkers(GridScene *scene);

BOOL MoveGridCursorUp(GridScene *scene)
{
    GridCursor *cursor = GRID_CURSOR(scene);
    int wrapped;
    int moved;
    int width;
    int col;
    int row;
    int stride;
    int startPos;
    int pos;
    GridCell *startCell;
    GridCell *cell;
    GridSlot *slot;
    int delta;
    int value;

    startPos = cursor->pos;
    width = cursor->width;
    col = startPos % width;
    wrapped = 0;
    moved = 0;

    startCell = GetGridCell(col, startPos / width, scene);
    do {
        pos = cursor->pos - cursor->width;
        cursor->pos = pos;
        if (pos < 0) {
            if ((data_02060500 & 0x40) && wrapped == 0) {
                moved = 1;
                cursor->pos = cursor->width * (cursor->rows - 1) + col;
                startPos = cursor->width * cursor->rows + col;
                cursor->scroll = 0x1fa;
                cursor->scrollTimer = 0x12;
                wrapped++;
            } else {
                cursor->pos = startPos;
                return FALSE;
            }
        }
        stride = cursor->width;
        pos = cursor->pos;
        col = pos % stride;
        row = pos / stride;
        if (row < 0) {
            cursor->pos += stride;
            return FALSE;
        }
        cell = GetGridCell(col, row, scene);
    } while (cell == NULL);

    if (cell->y <= cursor->viewTop + cursor->scroll) {
        cursor->scrollTimer--;
        delta = cursor->scroll + (cell->y - startCell->y);
        cursor->scroll = delta;
        if (delta <= 0) {
            if (cursor->slot > 0) {
                slot = &scene->slots[cursor->slot];
                slot->b += delta;
                SetGridEntryPosition(0, cursor->slot, slot->a, slot->b, scene);
            }
            cursor->scroll = 0;
        }
        scene->selectedId = cell->id;
        RefreshCursorMarkers(scene);
        return TRUE;
    }

    if (moved == 1) {
        if (cursor->slot > 0) {
            slot = &scene->slots[cursor->slot];
            value = 0x96;
            if (col != 12) {
                value = 0xa6;
            }
            slot->b = value;
            SetGridEntryPosition(0, cursor->slot, slot->a, slot->b, scene);
        }
        scene->selectedId = cell->id;
        RefreshCursorMarkers(scene);
    } else {
        if (cursor->slot > 0) {
            slot = &scene->slots[cursor->slot];
            slot->b += cell->y - startCell->y;
            SetGridEntryPosition(0, cursor->slot, slot->a, slot->b, scene);
        }
        scene->selectedId = cell->id;
    }
    return TRUE;
}






