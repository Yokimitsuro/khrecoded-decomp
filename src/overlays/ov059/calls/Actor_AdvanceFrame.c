#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorActionEndFunc)(Actor *actor, int result, int arg);
typedef void (*ActorAngleFunc)(Actor *actor, u16 angle);

typedef struct ActorModel {
    u32 flags;
    u8 animation[1];
} ActorModel;

struct Actor {
    u8 pad_0000[0x1f8];
    ActorActionEndFunc onActionEnd;
    u8 pad_01fc[0x210 - 0x1fc];
    ActorAngleFunc onAngle;
    u8 pad_0214[0x230 - 0x214];
    ActorModel *model;
    u32 modelFlags;
    u8 pad_0238[0x75c - 0x238];
    s32 action;
    s32 actionFrame;
    u8 pad_0764[4];
    s32 actionDone;
    u8 pad_076c[0x930 - 0x76c];
    u8 playerIndex;
    u8 pad_0931[0x958 - 0x931];
    fx32 timeScale;
    u8 pad_095c[4];
    u16 angle;
    u8 pad_0962[0x994 - 0x962];
    s8 hitIndex;
    u8 pad_0995[3];
    u8 cueTable[0x9d4 - 0x998];
    u8 trackers[2][0x230];
    u8 pad_0e34[0xec4 - 0xe34];
    u8 motion[0x17fc - 0xec4];
    u32 sound;
    u8 pad_1800[0x1820 - 0x1800];
    s32 guardStock;
};

extern int func_ov001_02063a4c(void);
extern void StopSeqArcOrDefault(int seqArcNo, int player, int fadeFrames);
extern void StopSoundSeqHandle(u32 handle);
extern fx32 GetField28(void);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void func_ov021_020a8198(void *owner, int id);
extern fx32 func_ov031_020bc060(void);
extern fx32 GetSeekStep(void);
extern u16 AdvanceAnimationTracks(void *state, fx32 delta);
extern fx32 Anim_GetFrame(void *anim, int channel);
extern u16 GetLinkedAngleOffset_020cd104(Actor *actor);
extern void func_ov021_020a9ac4(void *object, fx32 delta);
extern void func_ov021_020aafe4(void *entry, fx32 value);
extern void func_ov021_020a8b08(int playerIndex, fx32 delta);
extern int func_ov001_0206db8c(int index);
extern BOOL func_ov021_020a8d3c(int groupId, int index);
extern void func_ov021_020a7fc4(void *table, int groupId, s32 time);

void Actor_AdvanceFrame(Actor *actor, fx32 delta)
{
    fx32 speed;
    int events;
    int i;
    u16 angle;

    if (func_ov001_02063a4c() == 7 || func_ov001_02063a4c() == 8) {
        StopSeqArcOrDefault(0xcd, 0, 5);
        StopSoundSeqHandle(actor->sound);
    }
    if (actor->action == 1) {
        speed = FX_Mul(delta, FX_Div(GetField28(), 0x333));
        if (actor->actionDone) {
            func_ov021_020a8198(actor->cueTable, 1);
        }
    } else {
        speed = delta;
    }
    if (actor->hitIndex == -1 && (actor->action == 1 || actor->action == 0 || actor->actionDone)) {
        if (actor->actionDone && !(actor->modelFlags & 4)) {
            if (actor->onActionEnd != NULL) {
                actor->onActionEnd(actor, 3, -1);
            }
        } else {
            fx32 end = func_ov031_020bc060();
            fx32 frame = GetField28();
            fx32 remaining = end - frame;

            if (remaining != 0) {
                FX_Div(remaining, GetSeekStep());
                if (actor->onActionEnd != NULL) {
                    BOOL moving = TRUE;
                    if (frame == 0) {
                        moving = FALSE;
                    }
                    actor->onActionEnd(actor, moving, -1);
                }
            } else if (func_ov001_02063a4c() == 4 || actor->action < 0x12) {
                if (actor->onActionEnd != NULL) {
                    BOOL moving = TRUE;
                    if (frame == 0) {
                        moving = FALSE;
                    }
                    actor->onActionEnd(actor, moving, -1);
                }
            }
        }
    }
    if (actor->action != -1) {
        events = (s16)AdvanceAnimationTracks(actor->model->animation, speed);
        actor->actionFrame = Anim_GetFrame(actor->model->animation, 0);
    }
    actor->angle = GetLinkedAngleOffset_020cd104(actor);
    actor->actionDone = FALSE;
    if (events & 1) {
        actor->actionDone = TRUE;
    }
    for (i = 0; i < 2; i++) {
        func_ov021_020a9ac4(actor->trackers[i], speed);
    }
    func_ov021_020aafe4(actor->motion, delta);
    if (actor->onAngle != NULL) {
        actor->onAngle(actor, 0);
    }
    func_ov021_020a8b08(actor->playerIndex, FX_Div(delta, actor->timeScale));
    angle = actor->angle;
    if (actor->onAngle != NULL) {
        actor->onAngle(actor, angle);
    }
    if (actor->guardStock >= 0 && !func_ov021_020a8d3c(func_ov001_0206db8c(0), actor->guardStock)) {
        actor->guardStock = -1;
    }
    func_ov021_020a7fc4(actor->cueTable, actor->action, actor->actionFrame);
}
