#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    int pad_00;
    int target;
    fx32 speed;
    int step;
    VecFx32 dir;
    u8 pad_1c[2];
    u16 counter;
    fx32 riseTimer;
    fx32 fallTimer;
    fx32 boost;
    u8 pad_2c[4];
    fx32 delay;
    u8 pad_34[8];
    s8 phase;
} GlideState;

typedef struct Actor Actor;
typedef void (*ModeFunc)(Actor *actor, int mode, int arg);
typedef void (*NotifyFunc)(Actor *actor, int arg);
typedef void (*TurnFunc)(Actor *actor, u16 angle);
typedef int (*StateGetter)(Actor *actor);
typedef void (*EventFunc)(Actor *actor, int event);

struct Actor {
    u8 pad_0000[0x1dc];
    int state;
    u8 pad_01e0[0x1f8 - 0x1e0];
    ModeFunc onMode;
    NotifyFunc onNotify;
    u8 pad_0200[0x210 - 0x200];
    TurnFunc onTurn;
    u8 pad_0214[0x22c - 0x214];
    StateGetter getState;
    u8 pad_0230[4];
    u32 modelFlags;
    u8 pad_0238[0x75c - 0x238];
    int mode;
    fx32 frame;
    u8 pad_0764[4];
    BOOL modeChangePending;
    u8 pad_076c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 player;
    u8 pad_09b5[0x9c4 - 0x9b5];
    fx32 groundSpeed;
    VecFx32 velocity;
    u8 pad_09d4[0x9ec - 0x9d4];
    fx32 frameStep;
    u8 pad_09f0[0xa10 - 0x9f0];
    GlideState glide;
    u8 pad_0a50[0x10ec - 0xa50];
    EventFunc onEvent;
};

extern void *func_ov001_0206db78(int player);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern BOOL func_ov001_0206e2b0(void);
extern BOOL func_ov021_020a7524(void *unit);
extern int func_ov021_020a7564(void *unit);
extern u16 SharedObject_GetFlagsB(void *unit);
extern fx32 ApproachTargetValue(GlideState *glide);
extern int ComputeFacingAndDirection(Actor *actor, VecFx32 *out);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern BOOL ReactToEvent(Actor *actor, GlideState *glide);
extern BOOL IsLockedOnActiveFieldUnit(Actor *actor);

static inline int GetActorState(Actor *actor)
{
    if (actor->getState != NULL) {
        return actor->getState(actor);
    }
    return actor->state;
}

void UpdateGlideState(Actor *actor)
{
    VecFx32 dir;
    void *unit;
    BOOL heavy;
    BOOL pressed;
    GlideState *glide = &actor->glide;
    BOOL active;
    BOOL steer;
    fx32 speed;
    int angle;
    fx32 minRise;
    fx32 velY;

    unit = func_ov001_0206db78(actor->player);
    heavy = FALSE;
    if (IsPlayerEntryFlagSet(0, 0xc) && !(actor->stateFlags & 0x400000000ULL) && !func_ov001_0206e2b0()) {
        heavy = TRUE;
    }
    active = FALSE;
    switch (glide->phase) {
    case 0:
        if (!(actor->stateFlags & 0x1000) && glide->boost == 0) {
            active = TRUE;
        }
        break;
    case 1:
    case 2:
        active = TRUE;
        break;
    }
    steer = FALSE;
    dir.z = 0;
    dir.y = 0;
    dir.x = 0;
    if (active) {
        if (glide->delay == 0) {
            if (func_ov021_020a7524(unit) && !(actor->stateFlags & 0x4000)) {
                steer = TRUE;
            }
        } else {
            glide->delay -= actor->frameStep;
            if (glide->delay < 0) {
                glide->delay = 0;
            }
        }
        if (steer) {
            speed = ApproachTargetValue(glide);
            angle = ComputeFacingAndDirection(actor, &dir);
            if (actor->onTurn != NULL) {
                actor->onTurn(actor, angle);
            }
            if (angle != func_ov021_020a7564(unit)) {
                speed = 1;
            }
        } else {
            dir = glide->dir;
            speed = 0xe14;
            glide->speed = FX_Mul(glide->speed, speed);
        }
    } else if (!func_ov021_020a7524(unit)) {
        glide->speed = 0;
    }
    dir.x = FX_Mul(dir.x, speed);
    dir.z = FX_Mul(dir.z, speed);
    actor->velocity.x += dir.x;
    actor->velocity.z += dir.z;
    glide->dir = dir;
    if (ReactToEvent(actor, glide)) {
        return;
    }
    switch (glide->phase) {
    case 0:
        if (actor->frame >= 0x1000) {
            minRise = 0x580;
            if (heavy) {
                minRise = 0x740;
            }
            glide->phase = 1;
            if (GetActorState(actor) != 4 && actor->velocity.y < minRise) {
                actor->velocity.y = minRise;
                return;
            }
        }
        break;
    case 1:
        velY = actor->velocity.y;
        pressed = FALSE;
        if ((SharedObject_GetFlagsB(unit) & 2) || (actor->stateFlags & 0x1000)) {
            pressed = TRUE;
        }
        if (glide->boost > 0) {
            glide->boost -= 0x1000;
            pressed = TRUE;
        }
        if ((!pressed || (actor->modelFlags & 8)) && actor->groundSpeed >= 0x3000 && velY > 0) {
            actor->velocity.y = velY >> 1;
        }
        if (actor->mode != 0xc && actor->frame >= 0x8000 && actor->onMode != NULL) {
            actor->onMode(actor, 0xc, -1);
        }
        if (velY <= 0) {
            if (actor->mode != 0xc && actor->onMode != NULL) {
                actor->onMode(actor, 0xc, -1);
            }
            glide->fallTimer += actor->frameStep;
            if (!heavy) {
                if (glide->fallTimer <= 0x4000) {
                    actor->velocity.y = 0;
                }
            } else if (glide->fallTimer <= 0x2000) {
                actor->velocity.y = 0;
            }
        }
        if (actor->velocity.y < 0) {
            glide->phase = 2;
        }
    case 2:
        if (glide->phase == 2) {
            glide->riseTimer += actor->frameStep;
        }
        if ((actor->stateFlags & 0x100) && glide->riseTimer >= 0xa000) {
            actor->stateFlags &= ~0x100ULL;
        }
        if (actor->modeChangePending && actor->mode == 0xc && actor->onNotify != NULL) {
            actor->onNotify(actor, 0xf000);
        }
        if (actor->modelFlags & 4) {
            actor->onEvent(actor, 5);
            if (IsLockedOnActiveFieldUnit(actor)) {
                actor->stateFlags |= 0x400000000ULL;
                return;
            }
        } else if (glide->phase == 2) {
            if (!heavy) {
                actor->velocity.y -= 0x50;
                return;
            }
            actor->velocity.y -= 0x80;
            return;
        }
        break;
    case 3:
        actor->modelFlags |= 0x40;
        if (!(actor->modelFlags & 4)) {
            if (actor->velocity.y < 0) {
                actor->velocity.y = -0x380;
                actor->onEvent(actor, 4);
            } else {
                actor->stateFlags |= 0x1000;
                actor->onEvent(actor, 3);
            }
        }
        if (actor->modeChangePending) {
            if (actor->onMode != NULL) {
                actor->onMode(actor, 0, -1);
            }
            actor->onEvent(actor, 1);
        }
        break;
    }
}
