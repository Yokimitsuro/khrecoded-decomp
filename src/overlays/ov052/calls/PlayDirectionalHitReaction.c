#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Entity Entity;

struct Entity {
    u8 pad_000[0x1f8];
    void (*playAnimation)(Entity *entity, int animId, int loopCount);
    void (*setAnimationFrame)(Entity *entity, int frame);
    u8 pad_200[0x210 - 0x200];
    void (*setFacing)(Entity *entity, u16 angle);
    u8 pad_214[0x9e0 - 0x214];
    VecFx32 velocity;
};

extern u16 GetLinkedAngleOffset(Entity *entity);
extern void VEC_Normalize(VecFx32 *src, VecFx32 *dst);
extern int FX_Atan2Idx(fx32 y, fx32 x);
extern u32 func_0202a9e4(u32 range);

void PlayDirectionalHitReaction(Entity *entity)
{
    u16 facing = GetLinkedAngleOffset(entity);
    int angle;
    int turn;
    u32 coin;
    int animId;
    VecFx32 direction;

    direction = entity->velocity;
    direction.y = 0;
    if (direction.x != 0 || direction.y != 0 || direction.z != 0) {
        VEC_Normalize(&direction, &direction);
        angle = (u16)FX_Atan2Idx(-direction.x, -direction.z);
    } else {
        angle = (u16)(facing - 0x8000);
    }
    turn = (u16)(angle - facing);
    if (turn > 0x8000) {
        turn = (u16)(0x10000 - turn);
    }
    coin = func_0202a9e4(2);
    if (turn > 0x4000) {
        if (coin & 1) {
            animId = 6;
        } else {
            animId = 7;
        }
        angle = (u16)(angle + 0x8000);
    } else {
        if (coin & 1) {
            animId = 8;
        } else {
            animId = 9;
        }
    }
    if (entity->playAnimation != NULL) {
        entity->playAnimation(entity, animId, -1);
    }
    if (entity->setAnimationFrame != NULL) {
        entity->setAnimationFrame(entity, 0);
    }
    if (entity->setFacing != NULL) {
        entity->setFacing(entity, angle);
    }
}
