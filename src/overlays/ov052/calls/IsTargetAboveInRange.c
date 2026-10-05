#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Entity Entity;

struct Entity {
    u8 pad_000[0x1DC];
    int currentState;
    u8 pad_1E0[0x48];
    BOOL (*isTargetValid)(Entity *entity, int mode);
    int (*getState)(Entity *entity);
    u8 pad_230[0x4];
    u32 controlFlags;
    u8 pad_238[0xE10];
    u8 target[4];
};

extern VecFx32 *func_ov001_0206c3f4(void *target);
extern VecFx32 *func_ov052_020ceb74(Entity *entity);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);

BOOL IsTargetAboveInRange(Entity *entity)
{
    BOOL inRange = FALSE;
    int state;
    int valid;

    if ((entity->controlFlags & 4) == 0) {
        return FALSE;
    }
    if (entity->getState != NULL) {
        state = entity->getState(entity);
    } else {
        state = entity->currentState;
    }
    if (state == 6) {
        return FALSE;
    }
    if (entity->isTargetValid != NULL) {
        valid = entity->isTargetValid(entity, 0);
    } else {
        valid = 0;
    }
    if (valid != 0) {
        VecFx32 *targetPos = func_ov001_0206c3f4(entity->target);
        VecFx32 *selfPos = func_ov052_020ceb74(entity);
        VecFx32 delta;

        func_01ff9e3c(targetPos, selfPos, &delta);
        delta.y = 0;
        if (targetPos->y - selfPos->y >= 0x2000 && VEC_Mag(&delta) <= 0x6000) {
            inRange = TRUE;
        }
    }
    return inRange;
}
