#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    int member;
    int action;
} MenuChoice;

typedef struct {
    int target;
    u8 pad_04[0x30];
    int cooldown;
    int recoverTime;
} ActionTimers;

typedef struct {
    u8 pad_00[0xc4];
    int dashSpeed;
} DashState;

typedef struct {
    u16 flags;
    u8 pad_02[0x7c];
    u16 frame;
} BodyAnim;

typedef struct {
    u32 pad_00;
    BodyAnim anim;
} BodyModel;

typedef struct Actor Actor;
typedef int (*StateGetter)(Actor *actor);
typedef void (*TurnCallback)(Actor *actor, u16 angle);

struct Actor {
    u8 pad_0000[0x1dc];
    int state;
    u8 pad_01e0[0x210 - 0x1e0];
    TurnCallback onTurn;
    u8 pad_0214[0x22c - 0x214];
    StateGetter getState;
    BodyModel *body;
    u8 pad_0234[0x75c - 0x234];
    int busy;
    u8 pad_0760[0x9ac - 0x760];
    u64 flags;
    u8 player;
    u8 pad_09b5[7];
    MenuChoice choice;
    u8 pad_09c4[0x9cc - 0x9c4];
    fx32 velY;
    u8 pad_09d0[0xa10 - 0x9d0];
    ActionTimers timers;
    u8 pad_0a4c[0xa54 - 0xa4c];
    DashState dash;
    u8 pad_0b1c[0xfc8 - 0xb1c];
    u8 handle[0x1034 - 0xfc8];
    s8 slotA;
    u8 pad_1035;
    s8 slotB;
    u8 pad_1037[0x1070 - 0x1037];
    u8 members[4];
};

extern void *func_ov001_0206db78(int player);
extern BOOL CanUseMemberSlot(Actor *actor, int index);
extern BOOL func_ov052_020d0688(Actor *actor);
extern void func_ov052_020c7d48(Actor *actor, fx32 targetSpeed);
extern void func_ov021_020aa4e8(void *handle);
extern BOOL func_ov052_020c9648(Actor *actor, int nextState);
extern void func_ov001_02063a80(int index, int amount);
extern void func_ov052_020d1310(Actor *actor, int paused);
extern int func_ov001_02063a38(void);
extern BOOL func_ov021_020a7524(void *unit);
extern int func_ov021_020a7564(void *unit);
extern u16 SharedObject_GetField2(void *unit);
extern void func_ov021_020ad8f8(void *members);

BOOL ExitActorState(Actor *actor, int nextState, BOOL force)
{
    BOOL blocked = FALSE;
    void *unit = func_ov001_0206db78(actor->player);
    MenuChoice *choice = &actor->choice;
    ActionTimers *timers = &actor->timers;
    int state;
    int action;
    DashState *dash;

    if (!force) {
        switch (nextState) {
        case 2:
        case 0xd:
        case 0x12:
            if (actor->getState != NULL) {
                state = actor->getState(actor);
            } else {
                state = actor->state;
            }
            if (state == 6) {
                blocked = TRUE;
            }
            break;
        case 0x15:
            if (actor->slotA >= 0 && !CanUseMemberSlot(actor, actor->slotA)) {
                actor->slotA = -1;
                blocked = TRUE;
            }
            break;
        case 0x17:
            if (actor->slotB >= 0 && !func_ov052_020d0688(actor)) {
                actor->slotB = -1;
                blocked = TRUE;
            }
            break;
        case 0xf:
            if (actor->flags & 0x20000) {
                blocked = TRUE;
            }
            break;
        }
        if (blocked) {
            return blocked;
        }
    }
    if ((actor->flags & 0x400000000ULL) && nextState != 3 && nextState != 4) {
        actor->flags &= ~0x400000000ULL;
    }
    action = choice->action;
    switch (action) {
    case 1:
        func_ov052_020c7d48(actor, 0x1000);
        break;
    case 6:
    case 0x10:
        dash = &actor->dash;
        dash->dashSpeed = 0x9000;
        if (action != 6) {
            dash->dashSpeed = 0xf000;
        }
        actor->flags &= ~1ULL;
        break;
    case 8:
        actor->flags &= ~2ULL;
        func_ov052_020c7d48(actor, 0x1000);
        break;
    case 0x13:
        func_ov052_020d1310(actor, 0);
        break;
    case 0x14:
        timers->cooldown = 0x9000;
        break;
    case 10:
        actor->flags &= ~0x800000000ULL;
        break;
    case 0xc:
        if (nextState != 0xb) {
            func_ov021_020aa4e8(actor->handle);
        }
        break;
    case 0xb:
        if (nextState != 0xc) {
            func_ov021_020aa4e8(actor->handle);
        }
        if (func_ov052_020c9648(actor, nextState)) {
            func_ov001_02063a80(0xd, 1);
        }
        func_ov052_020d1310(actor, 0);
        if (nextState != 0x15 && nextState != 0x18) {
            actor->slotA = -1;
        }
        actor->flags &= ~0x80000ULL;
        actor->flags &= ~0x10000000ULL;
        func_ov052_020c7d48(actor, 0x1000);
        break;
    case 0x11: {
        BodyAnim *anim = &actor->body->anim;
        int angle;
        anim->frame = 0;
        anim->flags |= 0x20;
        timers->recoverTime = 0x3000;
        if (func_ov001_02063a38() == 4 && actor->busy == 0xf) {
            if (func_ov021_020a7524(unit)) {
                angle = func_ov021_020a7564(unit);
            } else {
                angle = SharedObject_GetField2(unit);
            }
            if (angle >= 0 && angle < 0x7fff) {
                if (actor->onTurn != NULL) {
                    actor->onTurn(actor, 0x3fff);
                }
            } else if (actor->onTurn != NULL) {
                actor->onTurn(actor, 0xc001);
            }
        }
        break;
    }
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1c:
        actor->flags &= ~0x4000ULL;
        actor->flags &= ~0x2000ULL;
        actor->flags &= ~0x80000ULL;
        actor->flags &= ~0x1000000ULL;
        actor->flags &= ~0x20000000ULL;
        actor->flags &= ~0x200000000ULL;
        actor->flags &= ~0x10000000ULL;
        actor->flags |= 0x8000;
        func_ov052_020d1310(actor, 0);
        actor->timers.target = 0;
        if (choice->action == 0x16 && func_ov052_020c9648(actor, nextState)) {
            func_ov001_02063a80(0xd, 1);
        }
        if (choice->action == 0x1c && nextState == 3) {
            actor->velY = 0;
        }
        func_ov021_020ad8f8(actor->members);
        break;
    case 0x1b:
        func_ov052_020d1310(actor, 0);
        break;
    }
    return FALSE;
}
