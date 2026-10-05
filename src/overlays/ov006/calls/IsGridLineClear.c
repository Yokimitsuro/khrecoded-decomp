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
    u8 pad_14[0x10];
    GridCell *cells;
} PathGrid;

extern u32 *func_ov001_0209c3e8(void);
extern long long _s32_div_f(int numerator, int denominator);

BOOL IsGridLineClear(PathGrid *grid, int fromCell, int toCell) {
    u32 *state = func_ov001_0209c3e8();
    s16 columns;
    int fromRow;
    int fromColumn;
    int toRow;
    int toColumn;
    int i;

    if (state != NULL && (*state & 1)) {
        return FALSE;
    }
    columns = grid->columns;
    fromRow = (int)_s32_div_f(fromCell, columns);
    fromColumn = (int)(_s32_div_f(fromCell, columns) >> 32);
    toRow = (int)_s32_div_f(toCell, columns);
    toColumn = (int)(_s32_div_f(toCell, columns) >> 32);
    if (fromRow != toRow && fromColumn != toColumn) {
        return FALSE;
    }
    if (fromRow < toRow) {
        for (i = fromRow; i <= toRow; i++) {
            if (grid->layer != grid->cells[fromColumn + i * columns].layer) {
                return FALSE;
            }
        }
    } else if (fromRow > toRow) {
        for (i = toRow; i <= fromRow; i++) {
            if (grid->layer != grid->cells[fromColumn + i * columns].layer) {
                return FALSE;
            }
        }
    }
    if (fromColumn < toColumn) {
        for (i = fromColumn; i <= toColumn; i++) {
            if (grid->layer != grid->cells[fromRow * columns + i].layer) {
                return FALSE;
            }
        }
    } else if (fromColumn > toColumn) {
        for (i = toColumn; i <= fromColumn; i++) {
            if (grid->layer != grid->cells[fromRow * columns + i].layer) {
                return FALSE;
            }
        }
    }
    return TRUE;
}
