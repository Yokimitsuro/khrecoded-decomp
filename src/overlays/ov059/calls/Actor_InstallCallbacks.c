#include "nitro/types.h"

typedef void (*ActorCallback)(void);

typedef struct Actor {
    u8 pad_000[0x1e0];
    ActorCallback onFree;
    ActorCallback onUpdate;
    ActorCallback onDraw;
    ActorCallback callback1ec;
    ActorCallback callback1f0;
    u8 pad_1f4[0x1f8 - 0x1f4];
    ActorCallback callback1f8;
    ActorCallback callback1fc;
    ActorCallback callback200;
    u8 pad_204[0x208 - 0x204];
    ActorCallback callback208;
    ActorCallback callback20c;
    ActorCallback callback210;
    ActorCallback onAddVelocity;
    u8 pad_218[0x21c - 0x218];
    ActorCallback onGetReadyFlags;
    ActorCallback callback220;
    ActorCallback callback224;
    u8 pad_228[0x930 - 0x228];
    u8 variant;
    u8 pad_931[0x1804 - 0x931];
    ActorCallback onEnter;
    ActorCallback onStep;
    ActorCallback onExit;
} Actor;

extern void func_ov021_020a75c4(Actor *actor, int kind, int variant);
extern void Actor_Update(void);
extern void Actor_ReleaseResources(void);
extern void func_ov059_020cbe00(void);
extern void Actor_AdvanceFrame(void);
extern void Actor_ChangeMotion(void);
extern void Actor_SetAnimFrame(void);
extern void Actor_TakeHit(void);
extern void Actor_PlaySurfaceSound(void);
extern void Actor_GetReadyFlags(void);
extern void Actor_ClearMotionState(void);
extern void Actor_AddExtraVelocity(void);
extern void SetLinkedAngleOffset(void);
extern void Actor_BuildJointHitSphere(void);
extern void GetObjectPayload964(void);
extern void Actor_SetJointBlendMode(void);
extern void func_ov059_020cc018(void);

void Actor_InstallCallbacks(Actor *actor)
{
    func_ov021_020a75c4(actor, 0, actor->variant);
    actor->onUpdate = Actor_Update;
    actor->onFree = Actor_ReleaseResources;
    actor->onDraw = func_ov059_020cbe00;
    actor->callback1ec = Actor_AdvanceFrame;
    actor->callback1f8 = Actor_ChangeMotion;
    actor->callback1fc = Actor_SetAnimFrame;
    actor->callback208 = Actor_TakeHit;
    actor->callback1f0 = Actor_PlaySurfaceSound;
    actor->onGetReadyFlags = Actor_GetReadyFlags;
    actor->callback20c = Actor_ClearMotionState;
    actor->onAddVelocity = Actor_AddExtraVelocity;
    actor->callback210 = SetLinkedAngleOffset;
    actor->callback220 = Actor_BuildJointHitSphere;
    actor->callback224 = GetObjectPayload964;
    actor->callback200 = Actor_SetJointBlendMode;
    actor->onStep = func_ov059_020cc018;
    actor->onEnter = NULL;
    actor->onExit = NULL;
}
