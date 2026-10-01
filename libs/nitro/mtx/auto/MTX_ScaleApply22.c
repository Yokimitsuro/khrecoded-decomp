#include "libs/nitro/mtx/mtx_types_internal.h"

void MTX_ScaleApply22(
    const MtxFx22 *src, MtxFx22 *dst, fx32 scaleX, fx32 scaleY)
{
    dst->_00 = (fx32)(((long long)scaleX * src->_00) >> 12);
    dst->_01 = (fx32)(((long long)scaleX * src->_01) >> 12);
    dst->_10 = (fx32)(((long long)scaleY * src->_10) >> 12);
    dst->_11 = (fx32)(((long long)scaleY * src->_11) >> 12);
}
