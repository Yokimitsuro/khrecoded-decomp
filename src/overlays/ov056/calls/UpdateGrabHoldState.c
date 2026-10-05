#include "nitro/types.h"
#include "nitro/fx_types.h"

struct Actor;
typedef void (*ActorEventFunc)(struct Actor *actor, int event);
typedef void (*ActorResetFunc)(struct Actor *actor, int arg, int target);

typedef struct {
    u8 pad_00[0x3d];
    s8 kind;
} EffectSource;

typedef struct {
    u8 pad_00[0xc];
    int eventArg;
    u8 pad_10[0x40 - 0x10];
    int hitLimit;
    int startFrame;
    int releaseFrame;
    int menuFrame;
    EffectSource *source;
} GrabWork;

typedef struct {
    u8 pad_00[0x40];
    s8 hitCount;
} HitCounter;

typedef struct Actor {
    u8 pad_0000[0x1f8];
    ActorResetFunc onReset;
    ActorEventFunc onHit;
    u8 pad_0200[0x234 - 0x200];
    u32 bodyFlags;
    u8 pad_0238[0x75c - 0x238];
    s32 motion;
    s32 frame;
    u8 pad_0764[0x768 - 0x764];
    s32 released;
    u8 pad_076c[0x9ac - 0x76c];
    u64 flags;
    u8 player;
    u8 pad_09b5[0x9c8 - 0x9b5];
    VecFx32 offset;
    u8 pad_09d4[0x9f8 - 0x9d4];
    fx32 pushSpeed;
    u8 pad_09fc[0xa10 - 0x9fc];
    HitCounter counter;
    u8 pad_0a51[0x1030 - 0xa51];
    s32 menuState;
    u8 pad_1034;
    s8 menuKind;
    u8 pad_1036[0x1078 - 0x1036];
    GrabWork *work;
    u8 pad_107c[0x10ec - 0x107c];
    ActorEventFunc setState;
} Actor;

extern void ComputeRootMotionDelta(Actor *actor, VecFx32 *out);
extern BOOL GetLockTargetPosition(Actor *actor, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL IsCountBelowLimit(EffectSource *source);
extern int MapKindToSlot(u32 kind);
extern s32 func_ov001_02063a38(void);
extern void DispatchSourceKindEvent(EffectSource *source, int slot, int arg);
extern void func_ov001_02078680(void);
extern BOOL HandleMemberMenuInput(Actor *actor);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern BOOL HandlePendingCommand(Actor *actor);

void UpdateGrabHoldState(Actor *actor)
{
    EffectSource *source;
    u32 grounded;
    BOOL landing;
    HitCounter *counter;
    GrabWork *work;
    VecFx32 delta;
    VecFx32 lock;
    int slot;

    grounded = actor->bodyFlags & 4;
    landing = FALSE;
    counter = &actor->counter;
    work = actor->work;
    source = work->source;

    ComputeRootMotionDelta(actor, &delta);
    if (grounded == 0 && actor->motion == 0x24) {
        landing = TRUE;
    }
    if (landing || delta.y != 0) {
        actor->offset.y = delta.y;
    }
    if (GetLockTargetPosition(actor, &lock)) {
        VEC_Add(&delta, &lock, &delta);
    }
    actor->offset.x += delta.x;
    actor->offset.z += delta.z;

    if (actor->released == 0 && (actor->flags & 0x2000) && work->releaseFrame > work->startFrame
        && actor->frame >= work->releaseFrame) {
        if (counter->hitCount < work->hitLimit) {
            if (IsCountBelowLimit(source)) {
                if (actor->onHit != NULL) {
                    actor->onHit(actor, 0x9000);
                }
                actor->flags &= ~0x2000;
            }
        } else if (actor->menuState == 6) {
            actor->released = 1;
        }
    }

    if (actor->frame >= work->startFrame && !(actor->flags & 0x2000)) {
        slot = MapKindToSlot(source->kind);
        if (slot == 0 && actor->motion != 0x1f) {
            slot = 1;
        }
        if (func_ov001_02063a38() == 6) {
            slot = actor->menuKind;
        }
        DispatchSourceKindEvent(source, slot, work->eventArg);
        actor->flags |= 0x2000;
        if (func_ov001_02063a38() == 6) {
            func_ov001_02078680();
        }
        counter->hitCount++;
    }

    if (counter->hitCount >= work->hitLimit && actor->frame >= work->menuFrame && work->menuFrame != 0
        && HandleMemberMenuInput(actor)) {
        actor->menuState = 6;
    }
    if (IsPlayerEntryFlagSet(actor->player, 0x15) && source->kind == 3) {
        actor->pushSpeed = 0x3000;
    }
    if (actor->released != 0) {
        actor->pushSpeed = 0;
        actor->flags &= ~0x2000;
        if (!HandlePendingCommand(actor)) {
            if (grounded) {
                if (actor->motion == 0x1f || actor->motion == 0x26) {
                    actor->setState(actor, 1);
                    if (actor->onReset != NULL) {
                        actor->onReset(actor, 0, -1);
                    }
                } else {
                    actor->setState(actor, 5);
                }
            } else {
                actor->setState(actor, 4);
            }
        }
    }
}
