#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Entity Entity;

typedef struct MotionState {
    u8 pad_00[0x24];
    fx32 speed;
} MotionState;

struct Entity {
    u8 pad_000[0x9AC];
    u64 stateFlags;
    u8 pad_9B4[0xC];
    int currentState;
    u8 pad_9C4[0x4];
    VecFx32 velocity;
    u8 pad_9D4[0x3C];
    MotionState motion;
    u8 pad_A38[0x6B4];
    void (*changeState)(Entity *entity, int state);
};

extern const s16 data_02053580[];
extern u16 func_ov052_020ceb9c(Entity *entity);
extern void func_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);

static inline void SetVecFx32(VecFx32 *vector, fx32 x, fx32 y, fx32 z)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

void EnterRecoilState(Entity *entity)
{
    MotionState *motion = &entity->motion;
    int angleIndex = (u16)(func_ov052_020ceb9c(entity) + 0x8000) >> 4;
    VecFx32 direction;

    direction.x = 0;
    direction.z = 0;
    direction.x = -data_02053580[angleIndex];
    direction.y = 0;
    direction.z = -data_02053580[(0x400 - angleIndex) & 0xfff];
    func_01ffafb4(0x100, &direction, &direction);
    if (entity->currentState == 6) {
        entity->velocity.y = 0;
        entity->changeState(entity, 4);
    } else {
        entity->changeState(entity, 4);
        motion->speed = 0x2000;
        entity->stateFlags |= 1;
    }
    SetVecFx32(&entity->velocity, direction.x, direction.y, direction.z);
}
