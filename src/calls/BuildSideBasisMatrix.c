#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct BasisMatrix {
    VecFx32 row[3];
} BasisMatrix;

extern void func_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *source, VecFx32 *dest);

void BuildSideBasisMatrix(const VecFx32 *up, const VecFx32 *forward, BasisMatrix *out)
{
    out->row[1] = *up;
    func_01ff9ea8(up, forward, &out->row[0]);
    VEC_Normalize(&out->row[0], &out->row[0]);
    func_01ff9ea8(&out->row[0], up, &out->row[2]);
}
