#include "nitro/types.h"

typedef struct Actor Actor;

typedef struct TargetInfo {
    u8 pad_00[0x3b];
    u8 lowBits : 4;
    u8 category : 4;
} TargetInfo;

typedef struct WaitTarget {
    u8 kind;
    u8 pad_01[3];
    TargetInfo *info;
} WaitTarget;

typedef struct TargetRequest {
    u8 selection;
    u8 flags;
} TargetRequest;

typedef struct MenuWork {
    u8 pad_0000[0x1264];
    int soloSelection;
    int pairSelection;
} MenuWork;

struct Actor {
    u8 pad_000[0x1dc];
    int state;
    u8 pad_1e0[0x22c - 0x1e0];
    int (*getState)(Actor *actor);
    u8 pad_230[0x234 - 0x230];
    u32 inputFlags;
    u8 pad_238[0x9ac - 0x238];
    u64 stateFlags;
    u8 selection;
    u8 pad_9b5[0x9c0 - 0x9b5];
    int timerDelay;
    u8 pad_9c4[0x1048 - 0x9c4];
    WaitTarget wait;
    u8 pad_1050[0x10ec - 0x1050];
    void (*setMode)(Actor *actor, int mode);
};

extern MenuWork *data_ov054_020d3720;
extern void *func_ov001_0206db78(u32 selection);
extern u16 SharedObject_GetId(void *self);
extern BOOL func_ov054_020d34d0(Actor *actor, int arg);
extern BOOL IsWaitTargetReady(WaitTarget *target);
extern u32 GetBoundedEntryField(int index);
extern BOOL IsEnemyStunnedOrDowned(u32 field);
extern void func_ov001_0207f8ac(TargetInfo *info, TargetRequest *request);
extern void MarkStateThreeFlag(Actor *actor);
extern void OpenFieldMenuMode(u32 kind);

static inline int GetActorState(Actor *actor)
{
    if (actor->getState != NULL) {
        return actor->getState(actor);
    }
    return actor->state;
}

BOOL HandleOverlay054MenuCommand(Actor *actor)
{
    MenuWork *work;
    BOOL result;
    void *entry;
    WaitTarget *wait;
    BOOL allowed;
    TargetRequest request;

    work = data_ov054_020d3720;
    entry = func_ov001_0206db78(actor->selection);
    result = FALSE;
    {
        u32 pressed = actor->inputFlags & 4;
        switch (SharedObject_GetId(entry)) {
        case 6:
            actor->setMode(actor, 0x1e);
            if (actor->timerDelay == 0x1e) {
                result = TRUE;
            }
            break;
        case 2:
        case 3:
            wait = &actor->wait;
            if (GetActorState(actor) != 3 && GetActorState(actor) != 2 && IsWaitTargetReady(&actor->wait) && wait->kind == 2) {
                allowed = TRUE;
                if (wait->info->category == 1 && pressed == 0) {
                    allowed = FALSE;
                }
                if (work->soloSelection > 0 && IsEnemyStunnedOrDowned(GetBoundedEntryField(work->soloSelection))) {
                    allowed = FALSE;
                }
                if (work->pairSelection > 0 && IsEnemyStunnedOrDowned(GetBoundedEntryField(work->pairSelection))) {
                    allowed = FALSE;
                }
                if (allowed) {
                    request.selection = actor->selection;
                    request.flags = 0;
                    func_ov001_0207f8ac(wait->info, &request);
                }
            }
            MarkStateThreeFlag(actor);
            break;
        case 4:
            if (pressed) {
                actor->stateFlags |= 0x20;
                OpenFieldMenuMode(1);
            }
            break;
        case 0:
            result = func_ov054_020d34d0(actor, 1);
            break;
        case 7:
            actor->setMode(actor, 0x1f);
            result = TRUE;
            break;
    }
    }
    return result;
}




