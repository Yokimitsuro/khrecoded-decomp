#include "nitro/types.h"
#include "nitro/fx_types.h"

struct Entity;
struct PoolNode;
struct FallState;

typedef struct EntityDef {
    u8 pad_00[0x30];
    BOOL (*isBusy)(struct Entity *entity);
    u8 pad_34[0x26];
    u8 kind;
} EntityDef;

typedef struct Entity {
    u8 pad_00[4];
    EntityDef *def;
    u8 pad_08[0x2a];
    u8 actorId;
    u8 slotIndex;
    u8 pad_34[4];
    VecFx32 position;
    u8 pad_44[6];
    s8 state;
} Entity;

typedef struct PoolNode {
    struct PoolNode *next;
    u32 slot : 8;
    s32 action : 8;
    u32 : 9;
    s32 pending : 1;
    u32 : 6;
} PoolNode;

typedef struct FallState {
    u8 falling;
    s8 targetGroup;
    s16 targetIndex;
    s32 fadeTimer;
} FallState;

typedef BOOL (*PoolHandler)(PoolNode *node, FallState *state, Entity *owner, Entity *entity);

typedef struct {
    PoolHandler handlers[4];
} HandlerTable;

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 position;
    s32 unk_0c;
    fx32 height;
} Shape;

typedef struct {
    u8 pad_000[0x119];
    u8 falling;
    u8 pad_11a[0x16];
    Shape *shape;
    Box box;
    u8 pad_14c[4];
    VecFx32 delta;
    Box sweptBox;
} Actor;

typedef struct {
    Entity *entity;
    s32 kind;
} HitLink;

typedef struct {
    u8 pad_00[0x68];
    HitLink link;
} HitTarget;

typedef struct {
    HitTarget *hit;
    s32 hitType;
    u8 pad_08[0x19c];
} QueryWorkspace;

typedef struct {
    void *func;
    void *context;
} QueryCallback;

typedef struct {
    s32 unk_00;
    s32 mask;
} QueryFilter;

typedef struct {
    u8 pad_00[0x48];
    QueryCallback filter;
    QueryCallback check;
    u8 pad_58[8];
} CollisionQuery;

extern const HandlerTable gPoolInitHandlers;

extern PoolNode **GetPool4Entry(Entity *owner, int index);
extern Entity *func_ov001_02086384(EntityDef *def, int index);
extern BOOL func_ov042_020bd7ac(void);
extern BOOL IsState2(Entity *entity);
extern void ResetFieldObjectToIdle(Entity *entity);
extern Actor *ActorRegistry_GetEntityByIndex(u32 id);
extern Entity *func_ov001_0208724c(int group, int index);
extern void *func_ov017_020a5e10(Entity *entity);
extern BOOL func_ov017_020a5dfc(void *handle);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern BOOL SweepWorldCollision(CollisionQuery *query);
extern BOOL CanUseSwitchTarget();
extern BOOL IsDeltaBeyond16();
extern u8 func_ov001_02086fcc(EntityDef *def);
extern Entity *func_ov017_020a5e08(Entity *entity);
extern fx32 EaseProgress(fx32 numer, fx32 denom, int mode);
extern void SetBrightnessAndSyncMain(int value);

static inline BOOL Entity_IsBusy(Entity *entity)
{
    if (entity->def->isBusy != NULL) {
        return entity->def->isBusy(entity);
    }
    return FALSE;
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

static inline QueryFilter MakeFilter(s32 value, s32 mask)
{
    QueryFilter filter;
    filter.unk_00 = value;
    filter.mask = mask;
    return filter;
}

static inline QueryCallback MakeCallback(void *func, void *context)
{
    QueryCallback callback;
    callback.func = func;
    callback.context = context;
    return callback;
}

int UpdateOwnerFall(FallState *state, Entity *owner, int poolIndex)
{
    PoolNode **pool;
    PoolNode *node;
    Actor *actor;
    HandlerTable table;
    CollisionQuery sweep;
    QueryWorkspace workspace;
    CollisionQuery query;
    QueryFilter filter;
    fx32 brightness;

    pool = GetPool4Entry(owner, poolIndex);
    table = gPoolInitHandlers;
    for (node = *pool; node != NULL; node = node->next) {
        if (node->pending) {
            Entity *entity = func_ov001_02086384(owner->def, node->slot);
            if (table.handlers[node->action](node, state, owner, entity)) {
                node->pending = 0;
            }
        }
    }
    if (Entity_IsBusy(owner)) {
        if (!func_ov042_020bd7ac() && IsState2(owner) && owner->state != 0) {
            ResetFieldObjectToIdle(owner);
        }
    } else {
        actor = ActorRegistry_GetEntityByIndex(owner->actorId);
        if (!state->falling && state->targetGroup != -1) {
            Entity *target = func_ov001_0208724c(state->targetGroup, state->targetIndex);
            BOOL startFall = FALSE;
            if (Entity_IsBusy(target)) {
                startFall = TRUE;
            } else if (target->def->kind == 7 && func_ov017_020a5dfc(func_ov017_020a5e10(target))) {
                startFall = TRUE;
            }
            if (startFall) {
                state->falling = 1;
                actor->falling = 1;
            }
        }
        if (state->falling) {
            filter = MakeFilter(0, 0x1d);
            actor->falling = 1;
            actor->delta = MakeVec(0, -0x600, 0);
            OffsetBoxByDelta(&actor->box, &actor->sweptBox, &actor->delta);
            CollisionQuery_Init(&query, 0, actor, 9, 1, 1, &actor->shape, &workspace, &filter);
            sweep = query;
            sweep.filter = MakeCallback(CanUseSwitchTarget, state);
            sweep.check = MakeCallback(IsDeltaBeyond16, state);
            if (SweepWorldCollision(&sweep)) {
                state->falling = 0;
                actor->falling = 0;
                if (workspace.hitType == 4) {
                    HitLink *link = &workspace.hit->link;
                    if (link->kind == 0x1b) {
                        state->targetGroup = func_ov001_02086fcc(link->entity->def);
                        state->targetIndex = func_ov017_020a5e08(link->entity)->slotIndex;
                    } else {
                        state->targetGroup = -1;
                    }
                } else {
                    state->targetGroup = -1;
                }
            }
            owner->position = actor->shape->position;
            owner->position.y -= actor->shape->height;
        }
    }
    if (state->fadeTimer != -1) {
        state->fadeTimer += 0x1000;
        if (state->fadeTimer >= 0x1e000) {
            state->fadeTimer = -1;
            brightness = 0;
        } else {
            brightness = ((0x1000 - EaseProgress(state->fadeTimer, 0x1e000, 0)) * 16) >> 12;
        }
        SetBrightnessAndSyncMain(brightness);
    }
    return 0;
}
