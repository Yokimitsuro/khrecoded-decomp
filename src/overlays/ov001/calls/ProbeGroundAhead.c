#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionQuery {
    VecFx32 *origin;
    VecFx32 *delta;
    int unk_08;
    u16 unk_0c;
    u16 layerMask;
    void *filter;
    u8 pad_14[0x4c];
} CollisionQuery;

typedef struct ActorBody {
    u8 pad_000[0x10c];
    u8 surface[0x1c2 - 0x10c];
    u16 eventId;
    u8 pad_1c4[0x25c - 0x1c4];
    u32 stateBits : 31;
    u32 stateTop : 1;
    u8 pad_260[0x354 - 0x260];
    int busy;
} ActorBody;

typedef struct FieldActor {
    u8 pad_000[0x10];
    ActorBody body;
} FieldActor;

extern int func_ov001_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern u8 *GetStageEventRecord(u32 id);
extern fx32 func_01ffaff4(VecFx32 *src, VecFx32 *dst);
extern fx32 Surface_GetKindValue(void *surface);
extern void VEC_MultAdd(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern int ResetAndQueryWorldCollision(CollisionQuery *query);

static inline s32 GetSessionMode(void)
{
    if (func_ov001_02063a24()) {
        return func_ov001_02063a38();
    }
    return 0;
}

int ProbeGroundAhead(FieldActor *actor, VecFx32 *base, VecFx32 *direction)
{
    ActorBody *body = &actor->body;
    u8 *event;
    VecFx32 point;
    VecFx32 unit;
    VecFx32 down;
    CollisionQuery query;

    if (GetSessionMode() == 7) {
        return 0;
    }
    event = GetStageEventRecord(actor->body.eventId);
    if (event == NULL) {
        return -1;
    }
    if (event[9] == 4) {
        return -1;
    }
    if (actor->body.busy != 0) {
        return -1;
    }
    if (actor->body.stateBits & 0x48) {
        return -1;
    }
    if (func_01ffaff4(direction, &unit) == 0) {
        return -1;
    }
    VEC_MultAdd(Surface_GetKindValue(body->surface) * 2, &unit, base, &point);
    down.x = 0;
    down.y = -0x1000;
    query.delta = &down;
    down.z = 0;
    query.origin = &point;
    query.unk_08 = 0;
    query.unk_0c = 0;
    query.layerMask = 0xcf;
    query.filter = &actor->body;
    return ResetAndQueryWorldCollision(&query);
}
