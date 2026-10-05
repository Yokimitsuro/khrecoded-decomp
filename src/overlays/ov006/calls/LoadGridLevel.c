#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 originX;
    fx32 originZ;
    fx32 cellSize;
    s16 rows;
    s16 columns;
    int level;
    u8 unk14[8];
    int pathCount;
    s32 *pathData;
    s32 *cells;
    int targetCount;
    s32 *targetData;
} GridInfo;

void LoadGridLevel(GridInfo *out, int level, s32 *data)
{
    GridInfo grids[4];
    u16 i;

    for (i = 0; i < 4; i++) {
        GridInfo *grid = &grids[i];
        grid->originX = data[0];
        grid->originZ = data[1];
        grid->cellSize = data[2];
        grid->columns = data[3];
        grid->rows = data[4];
        grid->cells = &data[5];
        data += grid->rows * grid->columns + 5;
    }
    data = (s32 *)((u8 *)data + (level - 1) * 300);
    *out = grids[data[0]];
    out->level = level;
    out->targetCount = data[1];
    out->targetData = &data[2];
    out->pathCount = data[49];
    out->pathData = &data[50];
}


