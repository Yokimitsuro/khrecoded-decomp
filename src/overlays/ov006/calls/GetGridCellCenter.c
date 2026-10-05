#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 originX;
    fx32 originZ;
    fx32 cellSize;
    s16 rows;
    s16 columns;
} GridInfo;

extern long long _s32_div_f(int numerator, int denominator);
extern void func_ov006_020a1344(GridInfo *grid, int row, int column, VecFx32 *out);

void GetGridCellCenter(GridInfo *grid, int cellIndex, VecFx32 *out)
{
    s16 columns = grid->columns;
    int row = (int)_s32_div_f(cellIndex, columns);
    int column = (int)(_s32_div_f(cellIndex, columns) >> 32);
    func_ov006_020a1344(grid, row, column, out);
}
