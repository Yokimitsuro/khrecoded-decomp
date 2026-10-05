#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorChangeStateFunc)(Actor *actor, s32 state);

typedef struct InputRecord InputRecord;

struct Actor {
    u8 pad_0000[0x928];
    u64 statusFlags;
    u8 pad_0930[0x944 - 0x930];
    s32 mode;
    u8 pad_0948[0x1708 - 0x948];
    s32 pendingCommand;
    s32 commandKinds[1];
    u8 pad_1710;
    s8 commandIndex;
    u8 pad_1712[0x171c - 0x1712];
    u32 chargePhase : 8;
    u32 chargeFlags : 24;
    u8 pad_1720[0x172c - 0x1720];
    s32 chargeTimer;
    u8 pad_1730[0x17fc - 0x1730];
    u32 chargeSound;
    u8 pad_1800[0x1808 - 0x1800];
    ActorChangeStateFunc changeState;
};

extern void func_ov059_020c9a74(Actor *actor, BOOL start);
extern int func_ov001_02077f80(void);
extern BOOL func_ov021_020a754c(InputRecord *input, u16 mask);
extern BOOL func_ov021_020a753c(InputRecord *input, u16 mask);
extern BOOL func_0204dc50(u32 handle);
extern u32 SpawnSoundSlot(u32 owner, u32 kind, VecFx32 *position, u32 flags);
extern VecFx32 *Actor_GetModelPosition(Actor *actor);
extern void func_ov059_020c7a90(Actor *actor);
extern void func_ov059_020c9a50(Actor *actor);
extern void func_ov001_0206e6f4(int arg);

void Actor_UpdateChargeCommand(Actor *actor, InputRecord *input)
{
    BOOL start = FALSE;
    s32 threshold;

    if ((actor->statusFlags & 0x10) || actor->pendingCommand != -1 || actor->mode == 7) {
        func_ov059_020c9a74(actor, FALSE);
        return;
    }
    if (func_ov001_02077f80() == -1) {
        func_ov059_020c9a74(actor, start);
        return;
    }
    switch (actor->commandKinds[actor->commandIndex]) {
    case 0:
        threshold = 0x1800;
        break;
    case 1:
        threshold = 0xf000;
        break;
    default:
        threshold = 0;
        break;
    }
    if (func_ov021_020a754c(input, 0x400) && !func_ov021_020a754c(input, 1)) {
        switch (actor->commandKinds[actor->commandIndex]) {
        case 0:
        case 1:
            if (actor->chargeTimer < threshold) {
                break;
            }
            if (actor->chargeTimer == 0x7fffffff) {
                actor->chargeTimer = 0;
            } else {
                actor->chargeTimer -= threshold;
            }
            if (actor->commandKinds[actor->commandIndex] == 0) {
                actor->chargePhase = 3;
                if (actor->chargeSound == 0 || !func_0204dc50(actor->chargeSound)) {
                    actor->chargeSound = SpawnSoundSlot(0xca, 0, Actor_GetModelPosition(actor), 0);
                    func_ov059_020c7a90(actor);
                }
            } else {
                actor->chargePhase = 4;
                if (func_ov021_020a753c(input, 0x400)) {
                    func_ov059_020c7a90(actor);
                }
            }
            actor->changeState(actor, 12);
            func_ov059_020c9a50(actor);
            break;
        case 2:
            actor->changeState(actor, 7);
            func_ov001_0206e6f4(0);
            break;
        case 3:
            start = TRUE;
            break;
        }
    } else if (actor->chargeTimer > threshold) {
        actor->chargeTimer = 0x7fffffff;
    }
    func_ov059_020c9a74(actor, start);
}
