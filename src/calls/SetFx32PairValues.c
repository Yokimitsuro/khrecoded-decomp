#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Fx32Pair {
    fx32 x;
    fx32 y;
} Fx32Pair;

void SetFx32PairValues(Fx32Pair *out, fx32 a, fx32 b)
{
    Fx32Pair pair;
    pair.x = a;
    pair.y = b;
    *out = pair;
}
