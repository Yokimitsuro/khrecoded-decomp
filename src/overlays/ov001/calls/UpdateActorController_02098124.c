#include "nitro/types.h"

typedef struct ActorAttributes {
    u32 value : 31;
    u32 locked : 1;
} ActorAttributes;

typedef struct StageActor {
    u8 pad_000[0x10];
    u8 body[0x1d0 - 0x10];
    u8 motion[0x26c - 0x1d0];
    ActorAttributes attributes;
    u8 pad_270[2];
    u16 motionActive;
    u8 pad_274[0x2f0 - 0x274];
    u32 scaleX;
    u32 scaleY;
    u32 scaleZ;
    u8 pad_2fc[0x31c - 0x2fc];
    u32 position;
    u8 pad_320[0x3a0 - 0x320];
    u32 anchor;
    u8 pad_3a4[0x3ac - 0x3a4];
    u16 anchorId;
} StageActor;

typedef struct StageEvent {
    u8 pad_00[0xa];
    u8 followAnchor;
    u8 pad_0b[5];
    u16 linkId;
} StageEvent;

typedef struct ActorController ActorController;

struct ActorController {
    s32 state;
    s32 nextState;
    u8 pad_08[2];
    u16 eventId;
    u16 actorId;
    u8 pad_0e[6];
    u32 scale;
    s32 timer;
};

typedef s32 (*ControllerStateFunc)(ActorController *controller);

extern ControllerStateFunc data_ov001_020a0318[];

extern StageActor *GetStageActor(int id);
extern StageEvent *GetStageEventRecord(u32 id);
extern u32 GetGlobalScaleValue(void);
extern void RunOverrideTrack(void *motion);
extern void func_ov001_02090308(StageActor *actor);

void UpdateActorController_02098124(ActorController *controller)
{
    StageActor *actor = GetStageActor((s16)controller->actorId);
    void *body = actor->body;
    StageActor *linked;
    StageEvent *event;
    s32 next;
    u32 scale;

    if (controller->nextState != 0 && controller->nextState != controller->state) {
        controller->state = controller->nextState;
        controller->nextState = 0;
    }
    next = data_ov001_020a0318[controller->state](controller);
    if (next != 0) {
        controller->nextState = next;
    }
    if (actor == NULL || controller->actorId == 0) {
        return;
    }
    if (actor->motionActive != 0) {
        RunOverrideTrack(actor->motion);
    }
    if (controller->timer > 0) {
        controller->timer -= GetGlobalScaleValue();
        if (controller->timer <= 0) {
            controller->timer = 0;
        }
    }
    if (actor->attributes.value & 1) {
        controller->state = 4;
        controller->nextState = 4;
    }
    if (body == NULL) {
        return;
    }
    if (controller->eventId != 0 && (event = GetStageEventRecord(controller->eventId)) != NULL &&
        event->linkId != 0 && (linked = GetStageActor((s16)event->linkId)) != NULL) {
        actor->position = linked->position;
        if (event->followAnchor && actor->anchorId == event->linkId) {
            actor->anchor = linked->anchor;
        }
    }
    scale = controller->scale;
    if (scale != 0) {
        actor->scaleX = scale;
        actor->scaleY = scale;
        actor->scaleZ = scale;
    }
    func_ov001_02090308(actor);
}
