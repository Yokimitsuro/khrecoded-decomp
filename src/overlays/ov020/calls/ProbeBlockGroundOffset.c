#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RayHit {
    u8 pad_00[0x2c];
    fx32 distance;
} RayHit;

typedef struct RayQuery {
    const VecFx32 *origin;
    const VecFx32 *direction;
    fx32 length;
    u16 mode;
    u16 mask;
    void *context;
    u8 pad_14[0x60 - 0x14];
} RayQuery;

typedef struct Block {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[8];
    fx32 dropOffset;
} Block;

extern const VecFx32 data_ov020_020a3a50;
extern int GetActorRegistry(void);
extern RayHit *func_020351cc(int handle, RayQuery *query);
extern void AddScaledVector(fx32 scale, const VecFx32 *scaledVector, const VecFx32 *baseVector,
                                    VecFx32 *resultVector);

void ProbeBlockGroundOffset(Block *block)
{
    VecFx32 down;
    VecFx32 hitPos;
    RayQuery query;
    RayHit *hit;
    fx32 diff;

    block->dropOffset = 0;
    down = data_ov020_020a3a50;
    query.direction = &down;
    query.origin = &block->position;
    query.length = 0x1800;
    query.mode = 1;
    query.mask = 0;
    query.context = block;
    hit = func_020351cc(GetActorRegistry(), &query);
    if (hit != NULL) {
        AddScaledVector(hit->distance, &down, &block->position, &hitPos);
        diff = block->position.y - hitPos.y;
        if (diff >= 0x19a && diff <= 0x7800) {
            block->dropOffset = hitPos.y - block->position.y + 0x1e0;
        }
    }
}
