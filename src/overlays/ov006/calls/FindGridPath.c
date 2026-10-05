#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 blocked;
    u8 distance;
    u8 pad_02[2];
} GridCell;

typedef struct {
    fx32 originX;
    fx32 originZ;
    fx32 cellSize;
    s16 rows;
    s16 columns;
    u8 pad_10[4];
    int goalCell;
    int found;
    u8 pad_1C[8];
    GridCell *cells;
} PathGrid;

extern long long _s32_div_f(int numerator, int denominator);
extern void func_ov006_020a1054(PathGrid *grid, int row, int column, int distance);
extern void func_ov006_020a10f8(PathGrid *grid, int row, int column);

int FindGridPath(PathGrid *grid, int goalCell, int startCell) {
    int i;
    s16 columns;

    for (i = 0; i < grid->rows * grid->columns; i++) {
        grid->cells[i].distance = 0;
    }
    grid->goalCell = goalCell;
    grid->cells[goalCell].distance = 0xff;
    grid->found = 0;
    columns = grid->columns;
    func_ov006_020a1054(grid, (int)_s32_div_f(startCell, columns), (int)(_s32_div_f(startCell, columns) >> 32), 1);
    columns = grid->columns;
    func_ov006_020a10f8(grid, (int)_s32_div_f(goalCell, columns), (int)(_s32_div_f(goalCell, columns) >> 32));
    return grid->found;
}
