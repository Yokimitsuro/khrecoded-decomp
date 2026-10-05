#include "nitro/types.h"

typedef struct {
    s32 originX;
    s32 originZ;
    s32 cellSize;
    s16 rows;
    s16 columns;
} GridInfo;

extern int _s32_div_f(int numerator, int denominator);

int GetGridCellIndex(GridInfo *grid, s32 *position)
{
    s16 columns = grid->columns;
    s32 cellSize = grid->cellSize;
    int column = _s32_div_f(position[0] - (grid->originX - ((columns * cellSize) >> 1)), cellSize);
    int row = _s32_div_f(position[2] - (grid->originZ - ((grid->rows * cellSize) >> 1)), cellSize);
    return column + row * columns;
}
