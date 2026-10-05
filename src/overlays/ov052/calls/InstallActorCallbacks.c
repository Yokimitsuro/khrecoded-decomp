#include "nitro/types.h"

typedef void (*ActorCallback)(void);

typedef struct Actor {
    u8 pad_000[0x1e0];
    ActorCallback onFree;
    ActorCallback onUpdate;
    ActorCallback onDraw;
    ActorCallback onAnimate;
    ActorCallback onSurfaceSound;
    u8 pad_1f4[4];
    ActorCallback onRequestMode;
    ActorCallback onSetAnimationFrame;
    ActorCallback onSetDisplayMode;
    ActorCallback onSetAlpha;
    ActorCallback onIncomingHit;
    ActorCallback onSetModeEnabled;
    ActorCallback onSetLinkedAngle;
    ActorCallback callback214;
    u8 pad_218[4];
    ActorCallback onBuildStatusFlags;
    ActorCallback onBuildHitSphere;
    ActorCallback callback224;
    ActorCallback onQueryTargetPosition;
    ActorCallback onGetState;
    u8 pad_230[0x9b4 - 0x230];
    u8 selectionIndex;
    u8 pad_9b5[0x10e8 - 0x9b5];
    s32 slotState;
    ActorCallback onSlotEvent;
    s32 slotParam0;
    s32 slotParam1;
    s32 slotParam2;
    ActorCallback trySlotAction;
} Actor;

extern void func_ov021_020a75c4(Actor *actor, int variant, int selectionIndex);
extern void RefreshActorState(void);
extern void DestroyActorResources(void);
extern void DrawActor(void);
extern void UpdateActorAnimation(void);
extern void RequestActorMode(void);
extern void SetAnimationFrameAll(void);
extern void ApplyIncomingHit(void);
extern void PlayActorContextSound(void);
extern void BuildActorStatusFlags(void);
extern void SetEntityModeEnabled(void);
extern void func_ov052_020ccfa0(void);
extern void SetLinkedAngleIfUnlocked(void);
extern void SetModelsAlpha(void);
extern void BuildSlot3HitSphere(void);
extern void func_ov052_020ccfbc(void);
extern void QueryTargetPosition(void);
extern void SetSlotDisplayMode(void);
extern void GetStateUnlessBlocked(void);
extern void func_ov052_020cd358(void);
extern void DispatchSlotAction(void);

void InstallActorCallbacks(Actor *actor)
{
    func_ov021_020a75c4(actor, 0, actor->selectionIndex);
    actor->onUpdate = RefreshActorState;
    actor->onFree = DestroyActorResources;
    actor->onDraw = DrawActor;
    actor->onAnimate = UpdateActorAnimation;
    actor->onRequestMode = RequestActorMode;
    actor->onSetAnimationFrame = SetAnimationFrameAll;
    actor->onIncomingHit = ApplyIncomingHit;
    actor->onSurfaceSound = PlayActorContextSound;
    actor->onBuildStatusFlags = BuildActorStatusFlags;
    actor->onSetModeEnabled = SetEntityModeEnabled;
    actor->callback214 = func_ov052_020ccfa0;
    actor->onSetLinkedAngle = SetLinkedAngleIfUnlocked;
    actor->onSetAlpha = SetModelsAlpha;
    actor->onBuildHitSphere = BuildSlot3HitSphere;
    actor->callback224 = func_ov052_020ccfbc;
    actor->onQueryTargetPosition = QueryTargetPosition;
    actor->onSetDisplayMode = SetSlotDisplayMode;
    actor->onGetState = GetStateUnlessBlocked;
    actor->onSlotEvent = func_ov052_020cd358;
    actor->slotState = 0;
    actor->slotParam0 = 0;
    actor->slotParam1 = 0;
    actor->slotParam2 = 0;
    actor->trySlotAction = DispatchSlotAction;
}
