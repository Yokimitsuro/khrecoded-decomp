#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct BasisMatrix {
    VecFx32 row[3];
} BasisMatrix;

extern void func_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *source, VecFx32 *dest);

void BuildBasisMatrix(const VecFx32 *forward, const VecFx32 *up, BasisMatrix *out)
{
    out->row[0] = *forward;
    func_01ff9ea8(up, forward, &out->row[1]);
    VEC_Normalize(&out->row[1], &out->row[1]);
    func_01ff9ea8(forward, &out->row[1], &out->row[2]);
}
