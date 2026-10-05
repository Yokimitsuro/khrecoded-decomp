#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Matrix33 {
    fx32 m[3][3];
} Matrix33;

extern void BuildBasisMatrix(int first, int second, Matrix33 *out);

void BuildMatrix33(Matrix33 *out, int first, int second)
{
    Matrix33 result;

    BuildBasisMatrix(first, second, &result);
    *out = result;
}
