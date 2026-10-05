#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x61];
    u8 locked;
    u8 pad_062[0x142];
    s32 pendingCount;
} StagePlayer;

typedef struct {
    u8 pad_00[4];
    u8 anim[2];
    s16 animId;
} ActorAnim;

typedef struct {
    u8 pad_000[0x10];
    ActorAnim anim;
    u8 pad_018[0x254];
    u32 moveFlags : 31;
    u32 moveFlagsHigh : 1;
    u8 pad_270[0x20];
    s32 height;
    u8 pad_294[8];
    s32 busy;
    u8 pad_2a0[0x24];
    s32 groundHeight;
    u8 pad_2c8[0x1e];
    u16 facing;
    u16 targetFacing;
    u8 pad_2ea[0x2a];
    s32 timer;
    s32 timerEnd;
    u8 pad_31c[0x4c];
    VecFx32 velocity;
} StageActor;

typedef struct {
    StagePlayer *player;
    u32 pad_04;
    StageActor *actor;
} StageGlobals;

typedef struct {
    u32 unk_00;
    u32 flags;
} WaitArgs;

extern StageGlobals data_ov021_020b56c4;
extern fx32 VEC_Mag(const VecFx32 *v);
extern int Anim_GetFrame(void *anim, int index);
extern int func_0202f4cc(void *anim, int index);
extern int ApplyActorScaleFactors(StageActor *actor);

int CheckWaitCondition(void *context, WaitArgs *args) {
    StageActor *actor = data_ov021_020b56c4.actor;
    StagePlayer *player = data_ov021_020b56c4.player;
    ActorAnim *anim = &actor->anim;
    if (actor != NULL) {
        u32 flags = args->flags;
        if (flags & 1) {
            int frame = Anim_GetFrame(anim->anim, 0);
            int end = func_0202f4cc(anim->anim, 0);
            if (anim->animId < 0) {
                return 3;
            }
            if (frame < end - ApplyActorScaleFactors(actor)) {
                return 3;
            }
        } else if (flags & 4) {
            if (actor->timer < actor->timerEnd) {
                return 3;
            }
        } else if (flags & 2) {
            if (actor->busy != 0) {
                return 3;
            }
        } else if (flags & 0x20) {
            if (actor->facing != actor->targetFacing) {
                return 3;
            }
        } else if (flags & 8) {
            fx32 speed = VEC_Mag(&actor->velocity);
            if (player->locked == 0 && !(actor->moveFlags & 8) && actor->groundHeight > actor->height) {
                return 3;
            }
            if (speed > 0x80) {
                return 3;
            }
        } else if (flags & 0x10) {
            if (player->pendingCount > 0) {
                return 3;
            }
        }
    }
    return 0;
}
