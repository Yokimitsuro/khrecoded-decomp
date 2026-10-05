#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x10];
    u8 collider[0x10c];
    u8 surface[0x1a4];
    VecFx32 position;
} PlayerActor;

typedef struct {
    u8 pad_00[8];
    PlayerActor *player;
} FieldContext;

typedef struct {
    u8 pad_00[0x34];
    VecFx32 position;
} ScriptObject;

typedef struct {
    u8 pad_00[8];
    s16 operand[4];
} ScriptCommand;

typedef struct {
    VecFx32 *start;
    VecFx32 *motion;
    fx32 radius;
    u16 pad_0c;
    u16 mask;
    void *ignore;
    u8 pad_14[0x4c];
} CollisionQuery;

typedef struct {
    u32 pad_00;
    u32 hit;
    u8 pad_08[0x24];
    fx32 fraction;
} CollisionResult;

extern FieldContext data_ov021_020b56c4;
extern const VecFx32 data_ov021_020b5124[8];
extern const VecFx32 data_0205344c;

extern s16 *ResolveTaggedValueRef(ScriptObject *obj, s16 *value);
extern s32 TaggedValueToFixed(s16 *tagged);
extern fx32 Surface_GetKindValue(void *surface);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern void func_ov001_02091c5c(PlayerActor *actor, VecFx32 *out);
extern void func_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern CollisionResult *QueryWorldMotionCollision(CollisionQuery *query);
extern CollisionResult *ResetAndQueryWorldCollision(CollisionQuery *query);
extern void AddScaledVector(fx32 scale, const VecFx32 *scaledVector, const VecFx32 *baseVector, VecFx32 *resultVector);

s32 ScriptOp_PlaceNearPlayerOnGround(ScriptObject *obj, ScriptCommand *cmd)
{
    s16 *distance = ResolveTaggedValueRef(obj, cmd->operand);
    PlayerActor *player = data_ov021_020b56c4.player;
    fx32 radius = FX_Mul(Surface_GetKindValue(player->surface), 0xb33);
    int i = 0;
    VecFx32 base;
    VecFx32 start;
    VecFx32 motion;
    CollisionQuery query;

    MI_CpuFill8(&query, 0, 0x60);
    func_ov001_02091c5c(player, &base);
    for (; i < 8; i++) {
        CollisionResult *result;
        start = base;
        start.y += 0x800;
        func_01ffa09c(TaggedValueToFixed(distance), &data_ov021_020b5124[i], &data_0205344c, &motion);
        MI_CpuFill8(&query, 0, 0x60);
        query.motion = &motion;
        query.start = &start;
        query.radius = radius;
        query.mask = 0x7f;
        query.ignore = player->collider;
        if (QueryWorldMotionCollision(&query) == NULL) {
            func_01ffa09c(TaggedValueToFixed(distance), &data_ov021_020b5124[i], &base, &start);
            start.y += 0xa000;
            motion.x = 0;
            motion.y = -0x14000;
            motion.z = 0;
            MI_CpuFill8(&query, 0, 0x60);
            query.motion = &motion;
            query.start = &start;
            query.radius = radius;
            query.mask = 0x7f;
            query.ignore = player->collider;
            result = ResetAndQueryWorldCollision(&query);
            if (result != NULL && result->hit != 0) {
                AddScaledVector(result->fraction, &motion, &start, &obj->position);
                return 0;
            }
        }
    }
    obj->position = player->position;
    return 0;
}
