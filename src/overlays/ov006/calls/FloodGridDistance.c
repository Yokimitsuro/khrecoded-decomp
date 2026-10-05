#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 layer;
    u8 distance;
    u8 pad_02[2];
} GridCell;

typedef struct {
    fx32 originX;
    fx32 originZ;
    fx32 cellSize;
    s16 rows;
    s16 columns;
    u32 layer;
    int goalCell;
    int found;
    u8 pad_1C[8];
    GridCell *cells;
} PathGrid;

typedef struct {
    int row;
    int column;
} GridStep;

extern const int data_ov006_020a1864[4];
extern const GridStep data_ov006_020a1884[];

int FloodGridDistance(PathGrid *grid, int row, int column, int distance) {
    int nextColumn;
    int nextRow;
    int cell;
    int i;

    cell = column + row * grid->columns;
    grid->cells[cell].distance = distance;
    if (cell == grid->goalCell) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        nextRow = row + data_ov006_020a1884[data_ov006_020a1864[i]].row;
        nextColumn = column + data_ov006_020a1884[data_ov006_020a1864[i]].column;
        if (nextRow < 0 || nextColumn < 0 || nextRow > grid->rows - 1 || nextColumn > grid->columns - 1) {
            continue;
        }
        cell = nextColumn + nextRow * grid->columns;
        if (grid->layer != grid->cells[cell].layer) {
            continue;
        }
        if (grid->cells[cell].distance == 0 || grid->cells[cell].distance > distance + 1) {
            FloodGridDistance(grid, nextRow, nextColumn, distance + 1);
        }
    }
    return 0;
}
