#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 type;
    u8 groupId;
    u8 entryId;
} EventInfo;

typedef struct {
    u8 pad_000[0x194];
    EventInfo event;
} LinkTarget;

typedef struct {
    u8 pad_00[0x14];
    LinkTarget *target;
} LinkHolder;

typedef struct {
    void *object;
    u32 flags;
    VecFx32 velocity;
} PhysicsBody;

typedef struct {
    u8 pad_00[0x10];
    LinkHolder *link;
    u8 pad_14[0xbc - 0x14];
    fx32 floorY;
    u8 pad_c0[4];
    int moveMode;
} MotionState;

typedef struct Actor Actor;
typedef int (*StateGetter)(Actor *actor);

struct Actor {
    u8 pad_0000[0x1dc];
    int state;
    u8 pad_01e0[0x22c - 0x1e0];
    StateGetter getState;
    PhysicsBody body;
    u8 pad_0244[0x25c - 0x244];
    fx32 fallSpeed;
    u8 pad_0260[0x274 - 0x260];
    MotionState motion;
    u8 pad_033c[0x4e5 - 0x33c];
    u8 grounded;
    u8 pad_04e6[0x9ac - 0x4e6];
    u64 flags;
    u8 pad_09b4[0x9c0 - 0x9b4];
    int stageType;
    u8 pad_09c4[4];
    VecFx32 velocity;
};

extern void ResolvePushVelocity(Actor *actor, VecFx32 *out);
extern VecFx32 *func_ov052_020ceb74(Actor *actor);
extern void func_02038e80(PhysicsBody *body, int arg);
extern void SweepActorBodyCapsule(Actor *actor);
extern int func_ov001_02067ed4(void);
extern fx32 func_ov001_02068070(void);
extern void Obj_SetPosition(void *object, const VecFx32 *position);
extern void SyncLockOnAnimSpeed(Actor *actor);
extern u32 GetPlayerEntryCount(int player, u32 id);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern BOOL IsLockedOnActiveFieldUnit(Actor *actor);
extern void *func_ov001_0208724c(u32 groupId, u32 entryId);
extern BOOL InitFieldUnitUpwardVelocity(void *unit);

static inline BOOL IsZeroVec(const VecFx32 *v)
{
    return v->x == 0 && v->y == 0 && v->z == 0;
}

void ApplyActorVelocity(Actor *actor)
{
    fx32 lastY = 0x7fffffff;
    VecFx32 vel;
    VecFx32 push;
    VecFx32 pos;
    VecFx32 landed;
    u64 flags;
    BOOL update;
    PhysicsBody *body;
    MotionState *motion;
    int state;

    vel.z = 0;
    vel.y = 0;
    vel.x = 0;
    flags = actor->flags;
    if (!(flags & 1) && !(flags & 0x20)) {
        vel = actor->velocity;
        if (!(flags & 0x800)) {
            ResolvePushVelocity(actor, &push);
            if (!IsZeroVec(&push)) {
                vel.x += push.x;
                vel.z += push.z;
                if (actor->getState != NULL) {
                    state = actor->getState(actor);
                } else {
                    state = actor->state;
                }
                if (state != 4) {
                    vel.y = push.y;
                } else {
                    vel.y += push.y;
                }
            }
        }
    } else {
        vel.y = actor->velocity.y;
    }
    update = FALSE;
    if (actor->fallSpeed != (fx32)0x80000000) {
        update = TRUE;
    } else if (vel.y != 0 || !(actor->body.flags & 4)) {
        update = TRUE;
    }
    if (update) {
        actor->fallSpeed = vel.y;
    }
    body = &actor->body;
    body->velocity.x = vel.x;
    body->velocity.y = 0;
    body->velocity.z = vel.z;
    if (!(actor->flags & 1)) {
        lastY = func_ov052_020ceb74(actor)->y;
        func_02038e80(&actor->body, 1);
    } else {
        actor->body.flags &= 0xffffc371;
        SweepActorBodyCapsule(actor);
    }
    actor->velocity.z = 0;
    actor->velocity.y = 0;
    actor->velocity.x = 0;
    actor->flags &= ~1ULL;
    {
        fx32 ground;
        func_ov001_02067ed4();
        ground = func_ov001_02068070();
        pos = *func_ov052_020ceb74(actor);
        if (pos.y > ground) {
            pos.y = ground;
            Obj_SetPosition(actor->body.object, &pos);
        }
    }
    SyncLockOnAnimSpeed(actor);
    if (!(actor->body.flags & 4)) {
        fx32 speed = actor->fallSpeed;
        if (speed == (fx32)0x80000000) {
            speed = 0;
        } else {
            fx32 limit = -0x380;
            if (actor->stageType == 0x11) {
                if (GetPlayerEntryCount(0, 0xe) > 1) {
                    limit = -0x21;
                } else {
                    limit = -0x26;
                }
            }
            if (actor->getState != NULL) {
                state = actor->getState(actor);
            } else {
                state = actor->state;
            }
            if (state == 4) {
                limit = FX_Mul(-0x380, 0xccd);
            }
            if (actor->flags & 0x80000) {
                limit = (fx32)0x80000000;
            }
            if (speed < limit) {
                speed = limit;
            }
        }
        actor->velocity.y = speed;
    }
    landed = *func_ov052_020ceb74(actor);
    if (actor->stageType == 0x11) {
        motion = &actor->motion;
        if (motion->moveMode != 0 && actor->grounded == 0 && lastY != landed.y) {
            fx32 floorY = motion->floorY + 0x400;
            if (floorY >= landed.y) {
                landed.y = floorY;
                Obj_SetPosition(actor->body.object, &landed);
                actor->body.flags &= ~4;
            }
        }
    }
    if (actor->body.flags & 4) {
        if (actor->flags & 0x8000000) {
            actor->flags &= ~0x8000000ULL;
        }
        if (actor->flags & 0x8000) {
            actor->flags &= ~0x8000ULL;
        }
        if (IsLockedOnActiveFieldUnit(actor)) {
            EventInfo *event = &actor->motion.link->target->event;
            void *unit = func_ov001_0208724c(event->groupId, event->entryId);
            int speed = 0;
            if (InitFieldUnitUpwardVelocity(unit)) {
                speed = 0x850;
            }
            if (speed != 0) {
                actor->velocity.y = speed;
                actor->flags |= 0x400000000ULL;
            }
        }
    }
}
