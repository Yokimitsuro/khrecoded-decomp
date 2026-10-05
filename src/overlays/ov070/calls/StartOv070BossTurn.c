#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct BossEntity BossEntity;

struct BossEntity {
    u8 pad_000[0x1f8];
    void (*notify)(BossEntity *entity, int arg1, int arg2);
    u8 pad_1fc[0x210 - 0x1fc];
    void (*onTurn)(BossEntity *entity, u16 angle);
    u8 pad_214[0x228 - 0x214];
    BOOL (*getTarget)(BossEntity *entity, VecFx32 *pos);
    u8 pad_22c[0x9ac - 0x22c];
    u64 flags;
    u8 pad_9b4[0xb2c - 0x9b4];
    u8 sound[4];
};

typedef struct {
    u8 pad_00[0x14];
    int player;
} SceneOwner;

typedef struct {
    u8 pad_00[0x40];
    u8 running;
    u8 pad_41[3];
    int field44;
    int field48;
    u8 pad_4c[0xc];
    int loopHandle;
} SceneObject;

extern BossEntity *GetBoundedEntryField(int index);
extern VecFx32 *func_ov052_020ceb74(BossEntity *entity);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern u16 FX_Atan2Idx(int y, int x);
extern void RestartScriptSound(void *sound, int arg);
extern void func_ov070_020d85e8();

void *StartOv070BossTurn(SceneOwner *owner, SceneObject *obj, int *wait)
{
    BossEntity *entity = GetBoundedEntryField(owner->player);
    VecFx32 dir;
    VecFx32 target;
    BOOL found = FALSE;
    u16 angle;

    obj->running = 0;
    obj->loopHandle = -1;
    obj->field44 = 0;
    obj->field48 = 0;
    if (entity->getTarget != NULL) {
        found = entity->getTarget(entity, &target);
    }
    if (found) {
        VEC_Subtract(&target, func_ov052_020ceb74(entity), &dir);
        dir.y = 0;
        if (VEC_DotProduct(&dir, &dir) > 0) {
            VEC_Normalize(&dir, &dir);
            angle = FX_Atan2Idx(dir.x, dir.z) + 0x8000;
            if (entity->onTurn != NULL) {
                entity->onTurn(entity, angle);
            }
        }
    }
    RestartScriptSound(entity->sound, 0);
    if (entity->notify != NULL) {
        entity->notify(entity, 0x27, -1);
    }
    entity->flags |= 0x40;
    *wait = 0x18;
    entity->flags |= 0x20000000;
    return func_ov070_020d85e8;
}
