#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 collider[0x10c];
    u8 surface[0x1a4];
} ActorBody;

typedef struct {
    u8 pad_00[0x10];
    ActorBody body;
    VecFx32 position;
} PlayerActor;

typedef struct {
    u8 pad_00[8];
    PlayerActor *player;
} FieldContext;

typedef struct {
    u8 pad_00[0x2c];
    u16 hasResult;
    u16 pad_2e;
    s32 result;
    VecFx32 position;
} ScriptObject;

typedef struct {
    u8 pad_00[8];
    s16 operand[4];
} ScriptCommand;

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    void *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    u8 data[0x10];
} ShapeStorage;

typedef struct {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct {
    u32 data[0x18];
} SweepQuery;

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
extern const VecFx32 data_ov021_020b5184[8];
extern const VecFx32 data_0205344c;

extern s16 *ResolveTaggedValueRef(ScriptObject *obj, s16 *value);
extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern fx32 Surface_GetKindValue(void *surface);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void NotifySceneObjectHandler(PlayerActor *actor, VecFx32 *out);
extern s32 _s32_div_f(s32 numerator, s32 denominator);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern CollisionShape func_0203ad28(ShapeStorage *storage, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init(SweepQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, SweptShape *shape, QueryWorkspace *workspace, void *filter);
extern void *SweepWorldCollision(SweepQuery *query);
extern CollisionResult *ResetAndQueryWorldCollision(CollisionQuery *query);
extern void AddScaledVector(fx32 scale, const VecFx32 *scaledVector, const VecFx32 *baseVector, VecFx32 *resultVector);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern fx32 VEC_Mag(const VecFx32 *v);

s32 ScriptOp_FindNearbyOpenCell(ScriptObject *obj, ScriptCommand *cmd)
{
    SweepQuery sweep;
    CollisionQuery query;
    QueryWorkspace workspace;
    SweptShape sweptCopy;
    SweptShape swept;
    SweepQuery initQuery;
    VecFx32 playerPos;
    VecFx32 cell;
    VecFx32 hitPos;
    VecFx32 start;
    VecFx32 motion;
    VecFx32 diff;
    ShapeStorage storage;
    VecFx32 zero;
    s32 filter[2];
    PlayerActor *player;
    ActorBody *body;
    fx32 best;
    fx32 radius;
    fx32 halfRadius;
    s32 i;

    ResolveTaggedValueRef(obj, cmd->operand);
    player = data_ov021_020b56c4.player;
    body = &player->body;
    obj->hasResult = 1;
    obj->result = 0;
    obj->position = player->position;
    MI_CpuFill8(&query, 0, 0x60);
    radius = FX_Mul(Surface_GetKindValue(body->surface), 0x1000);
    playerPos = player->position;
    NotifySceneObjectHandler(player, &cell);
    if (cell.x < 0) {
        cell.x = _s32_div_f(cell.x, 0x3000) * 0x3000 - 0x1800;
    } else {
        cell.x = _s32_div_f(cell.x, 0x3000) * 0x3000 + 0x1800;
    }
    if (cell.z < 0) {
        cell.z = _s32_div_f(cell.z, 0x3000) * 0x3000 - 0x1800;
    } else {
        cell.z = _s32_div_f(cell.z, 0x3000) * 0x3000 + 0x1800;
    }
    best = 0x7fffffff;
    zero = data_0205344c;
    halfRadius = radius >> 1;
    for (i = 0; i < 8; i++) {
        start = cell;
        start.y += 0x800;
        VEC_MultAdd(0x3000, &data_ov021_020b5184[i], &start, &start);
        swept.shape = func_0203ad28(&storage, &start, radius);
        swept.delta = zero;
        OffsetBoxByDelta(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
        sweptCopy = swept;
        CollisionQuery_Init(&initQuery, 0x70, body, 10, 1, 1, &sweptCopy, &workspace, filter);
        sweep = initQuery;
        if (SweepWorldCollision(&sweep) == NULL) {
            CollisionResult *result;

            VEC_MultAdd(0x3000, &data_ov021_020b5184[i], &cell, &start);
            start.y += 0xa000;
            motion.x = 0;
            motion.y = -0x14000;
            motion.z = 0;
            MI_CpuFill8(&query, 0, 0x60);
            query.motion = &motion;
            query.start = &start;
            query.radius = halfRadius;
            query.mask = 0x70;
            query.ignore = &player->body;
            result = ResetAndQueryWorldCollision(&query);
            if (result != NULL && result->hit != 0) {
                fx32 distance;

                AddScaledVector(result->fraction, &motion, &start, &hitPos);
                VEC_Subtract(&hitPos, &playerPos, &diff);
                if (VEC_Mag(&diff) >= 0xc00) {
                    VEC_Subtract(&hitPos, &cell, &diff);
                    distance = VEC_Mag(&diff);
                    if (distance <= 0x6000 && distance < best) {
                        best = distance;
                        obj->position = hitPos;
                        obj->result = 1;
                    }
                }
            }
        }
    }
    return 0;
}
