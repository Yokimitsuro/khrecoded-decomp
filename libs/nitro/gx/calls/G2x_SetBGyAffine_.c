#include "libs/nitro/mtx/mtx_types_internal.h"

void G2x_SetBGyAffine_(u32 address, const MtxFx22 *matrix,
                   int centerX, int centerY, int x1, int y1)
{
    s32 deltaX, deltaY;
    fx32 x2, y2;

    *((volatile u32 *)address + 0) =
        (u32)((u16)(s16)(matrix->_00 >> 4) |
              (u16)(s16)(matrix->_01 >> 4) << 16);
    *((volatile u32 *)address + 1) =
        (u32)((u16)(s16)(matrix->_10 >> 4) |
              (u16)(s16)(matrix->_11 >> 4) << 16);

    deltaX = x1 - centerX;
    deltaY = y1 - centerY;
    x2 = matrix->_00 * deltaX + matrix->_01 * deltaY + (centerX << 12);
    y2 = matrix->_10 * deltaX + matrix->_11 * deltaY + (centerY << 12);

    *((volatile u32 *)address + 2) = (u32)(x2 >> 4);
    *((volatile u32 *)address + 3) = (u32)(y2 >> 4);
}