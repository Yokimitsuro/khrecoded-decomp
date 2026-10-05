#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x4c];
    VecFx32 position;
} PathNode;

typedef struct {
    u8 pad_000[0x104];
    PathNode *nodes;
    s32 nodeIndex;
} PathFollower;

extern const VecFx32 data_0205344c;
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

void GetCurrentNodeOffset(PathFollower *follower, VecFx32 *out, VecFx32 *delta)
{
    VecFx32 position = follower->nodes[follower->nodeIndex].position;

    VEC_Subtract(&position, &data_0205344c, &position);
    if (delta != NULL) {
        VEC_Subtract(&position, out, delta);
    }
    *out = position;
}
