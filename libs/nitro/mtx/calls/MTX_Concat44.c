#include "libs/nitro/mtx/mtx_types_internal.h"

typedef long long fx64;

/* 4x4 fixed-point matrix concatenation. */
void MTX_Concat44(const MtxFx44 *a, const MtxFx44 *b, MtxFx44 *ab)
{
    MtxFx44 tmp;
    MtxFx44 *p;

    register fx32 row0, row1, row2, row3;
    register fx32 col0, col1, col2, col3;

    if (ab == b) {
        p = &tmp;
    } else {
        p = ab;
    }

    row0 = a->m[0][0];
    row1 = a->m[0][1];
    row2 = a->m[0][2];
    row3 = a->m[0][3];

    p->m[0][0] = (fx32)(((fx64)row0 * b->m[0][0] + (fx64)row1 * b->m[1][0] + (fx64)row2 * b->m[2][0] + (fx64)row3 * b->m[3][0]) >> 12);
    p->m[0][1] = (fx32)(((fx64)row0 * b->m[0][1] + (fx64)row1 * b->m[1][1] + (fx64)row2 * b->m[2][1] + (fx64)row3 * b->m[3][1]) >> 12);
    p->m[0][3] = (fx32)(((fx64)row0 * b->m[0][3] + (fx64)row1 * b->m[1][3] + (fx64)row2 * b->m[2][3] + (fx64)row3 * b->m[3][3]) >> 12);

    col0 = b->m[0][2];
    col1 = b->m[1][2];
    col2 = b->m[2][2];
    col3 = b->m[3][2];

    p->m[0][2] = (fx32)(((fx64)row0 * col0 + (fx64)row1 * col1 + (fx64)row2 * col2 + (fx64)row3 * col3) >> 12);

    row0 = a->m[1][0];
    row1 = a->m[1][1];
    row2 = a->m[1][2];
    row3 = a->m[1][3];

    p->m[1][2] = (fx32)(((fx64)row0 * col0 + (fx64)row1 * col1 + (fx64)row2 * col2 + (fx64)row3 * col3) >> 12);
    p->m[1][1] = (fx32)(((fx64)row0 * b->m[0][1] + (fx64)row1 * b->m[1][1] + (fx64)row2 * b->m[2][1] + (fx64)row3 * b->m[3][1]) >> 12);
    p->m[1][3] = (fx32)(((fx64)row0 * b->m[0][3] + (fx64)row1 * b->m[1][3] + (fx64)row2 * b->m[2][3] + (fx64)row3 * b->m[3][3]) >> 12);

    col0 = b->m[0][0];
    col1 = b->m[1][0];
    col2 = b->m[2][0];
    col3 = b->m[3][0];

    p->m[1][0] = (fx32)(((fx64)row0 * col0 + (fx64)row1 * col1 + (fx64)row2 * col2 + (fx64)row3 * col3) >> 12);

    row0 = a->m[2][0];
    row1 = a->m[2][1];
    row2 = a->m[2][2];
    row3 = a->m[2][3];

    p->m[2][0] = (fx32)(((fx64)row0 * col0 + (fx64)row1 * col1 + (fx64)row2 * col2 + (fx64)row3 * col3) >> 12);
    p->m[2][1] = (fx32)(((fx64)row0 * b->m[0][1] + (fx64)row1 * b->m[1][1] + (fx64)row2 * b->m[2][1] + (fx64)row3 * b->m[3][1]) >> 12);
    p->m[2][3] = (fx32)(((fx64)row0 * b->m[0][3] + (fx64)row1 * b->m[1][3] + (fx64)row2 * b->m[2][3] + (fx64)row3 * b->m[3][3]) >> 12);

    col0 = b->m[0][2];
    col1 = b->m[1][2];
    col2 = b->m[2][2];
    col3 = b->m[3][2];

    p->m[2][2] = (fx32)(((fx64)row0 * col0 + (fx64)row1 * col1 + (fx64)row2 * col2 + (fx64)row3 * col3) >> 12);

    row0 = a->m[3][0];
    row1 = a->m[3][1];
    row2 = a->m[3][2];
    row3 = a->m[3][3];

    p->m[3][2] = (fx32)(((fx64)row0 * col0 + (fx64)row1 * col1 + (fx64)row2 * col2 + (fx64)row3 * col3) >> 12);
    p->m[3][1] = (fx32)(((fx64)row0 * b->m[0][1] + (fx64)row1 * b->m[1][1] + (fx64)row2 * b->m[2][1] + (fx64)row3 * b->m[3][1]) >> 12);
    p->m[3][0] = (fx32)(((fx64)row0 * b->m[0][0] + (fx64)row1 * b->m[1][0] + (fx64)row2 * b->m[2][0] + (fx64)row3 * b->m[3][0]) >> 12);
    p->m[3][3] = (fx32)(((fx64)row0 * b->m[0][3] + (fx64)row1 * b->m[1][3] + (fx64)row2 * b->m[2][3] + (fx64)row3 * b->m[3][3]) >> 12);

    if (p == &tmp) {
        *ab = tmp;
    }
}
