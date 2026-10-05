#include "nitro/types.h"

typedef struct LayoutCell {
    u32 unk_00;
    u32 unk_04;
} LayoutCell;

extern LayoutCell data_ov001_0209e0ec;
extern LayoutCell data_ov001_0209e1a8[][6];

LayoutCell *GetLayoutCell(int row, int column, int offset)
{
    if (offset == 3) {
        return &data_ov001_0209e0ec;
    }
    return &data_ov001_0209e1a8[row][column + offset];
}
