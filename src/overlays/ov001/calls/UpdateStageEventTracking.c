#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorStateFlags {
    u32 bits : 31;
    u32 top : 1;
} ActorStateFlags;

typedef struct StageActor {
    u8 pad_000[0x26c];
    ActorStateFlags flags;
    u8 pad_270[0x282 - 0x270];
    u8 linkFlags;
    u8 updateFlags;
    u8 pad_284[0x288 - 0x284];
    u16 moveMode : 2;
    u16 moveBits : 14;
    u8 pad_28a[2];
    u16 lowBits : 3;
    u16 eventArgB : 4;
    u16 eventArgA : 4;
    u16 highBits : 5;
    u8 pad_28e[0x2e4 - 0x28e];
    u8 groupId;
} StageActor;

typedef struct StageEvent {
    u8 pad_000[9];
    u8 state;
    u8 pad_00a[0x10 - 0xa];
    s16 actorId;
    u8 pad_012[0x16 - 0x12];
    u16 motionId;
    u16 auxId;
    u8 pad_01a[0x1b4 - 0x1a];
    u8 holdA;
    u8 holdB;
    u8 pad_1b6[0x1bc - 0x1b6];
    u16 anchorId;
} StageEvent;

typedef struct MotionRecord {
    u16 active;
    u8 pad_02[2];
    VecFx32 position;
    VecFx32 previous;
    VecFx32 delta;
} MotionRecord;

typedef struct AuxRecord {
    u8 pad_00[8];
    void *source;
    u8 pad_0c[4];
    fx32 screenX;
    fx32 screenY;
    u8 pad_18[0x2a - 0x18];
    u8 visibility : 5;
    u8 visibilityHigh : 3;
} AuxRecord;

typedef struct ViewSource {
    u8 pad_00[0x14];
    VecFx32 eye;
    VecFx32 origin;
} ViewSource;

typedef struct AttachPoint {
    u32 key;
    const char *nodeName;
    VecFx32 offset;
    VecFx32 scale;
} AttachPoint;

extern char sOv001_TraTg_020a02fc[];
extern StageActor *FindRecordById_0209c304(u16 id);
extern StageActor *GetLinkedStageActor(StageActor *actor);
extern void func_ov001_02090a0c(StageActor *actor, int arg);
extern StageActor *GetStageActor(s16 id);
extern MotionRecord *GetStageMotionRecord(u16 id);
extern AuxRecord *GetStageAuxRecord(u16 id);
extern u16 FindActorResourceIndexByName(StageActor *actor, const char *name);
extern void GetNodePosition(StageActor *owner, u32 nodeId, VecFx32 *out);
extern u32 func_ov001_0209734c(StageEvent *event, StageActor *actor, int argA, int argB);
extern void FindStageAttachPoint(StageEvent *event, u32 key, AttachPoint *out);
extern ViewSource *func_ov021_020af614(void);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_01ffaff4(VecFx32 *in, VecFx32 *out);
extern int NNS_G3dWorldPosToScrPos(const VecFx32 *world, int *x, int *y);

void UpdateStageEventTracking(StageEvent *event)
{
    VecFx32 anchorPos;
    AttachPoint attach;
    VecFx32 toNode;
    VecFx32 axis;
    VecFx32 nodePos;
    VecFx32 tipPos;
    int nodeX;
    int tipX;
    int nodeY;
    int tipY;
    StageActor *record;
    StageActor *actor;
    MotionRecord *motion;
    AuxRecord *aux;
    StageActor *owner;
    ViewSource *view;
    int nodeResult;
    fx32 facing;
    int tipResult;
    BOOL refresh;
    int delta;

    actor = FindRecordById_0209c304(event->actorId);
    record = actor;
    refresh = TRUE;
    if (event->state != 3 && event->state != 4 && record->groupId == 0xff) {
        refresh = FALSE;
    }
    if (refresh) {
        for (; actor != NULL; actor = GetLinkedStageActor(actor)) {
            func_ov001_02090a0c(actor, 0);
        }
    }
    if (record->updateFlags & 1) {
        if (!(record->linkFlags & 1)) {
            event->holdA = 0;
        }
        event->holdB = 0;
    }
    if (event->motionId != 0 && event->anchorId != 0) {
        owner = GetStageActor(event->anchorId);
        motion = GetStageMotionRecord(event->motionId);
        if (motion != NULL && owner != NULL && motion->active != 0) {
            GetNodePosition(owner, FindActorResourceIndexByName(owner, sOv001_TraTg_020a02fc), &anchorPos);
            VEC_Subtract(&motion->position, &motion->previous, &motion->delta);
            motion->previous = motion->position;
            motion->position = anchorPos;
        }
    }
    for (actor = GetStageActor(event->actorId); actor != NULL; actor = GetLinkedStageActor(actor)) {
        if (actor->moveMode == 0 && actor->eventArgA != 0 && !(actor->flags.bits & 0x40000)) {
            func_ov001_0209734c(event, actor, actor->eventArgA, actor->eventArgB);
        }
    }
    if (event->auxId == 0) {
        return;
    }
    aux = GetStageAuxRecord(event->auxId);
    owner = GetStageActor(event->actorId);
    if (aux == NULL || aux->source == NULL) {
        return;
    }
    view = func_ov021_020af614();
    if (view != NULL) {
        FindStageAttachPoint(event, 5, &attach);
        GetNodePosition(owner, FindActorResourceIndexByName(owner, attach.nodeName), &nodePos);
        VEC_Add(&nodePos, &attach.offset, &tipPos);
        VEC_Subtract(&nodePos, &view->origin, &toNode);
        func_01ffaff4(&toNode, &toNode);
        VEC_Subtract(&view->eye, &view->origin, &axis);
        func_01ffaff4(&axis, &axis);
        facing = VEC_DotProduct(&toNode, &axis);
        nodeResult = NNS_G3dWorldPosToScrPos(&nodePos, &nodeX, &nodeY);
        tipResult = NNS_G3dWorldPosToScrPos(&tipPos, &tipX, &tipY);
        delta = tipY - nodeY;
        if (delta < 0) {
            delta = -delta;
        }
        if (delta < 10) {
            tipY = nodeY - 10;
        }
        delta = tipY - nodeY;
        if (delta < 0) {
            delta = -delta;
        }
        if (delta > 30) {
            tipY = nodeY - 30;
        }
        if (nodeResult < 0 || tipResult < 0 || facing <= 0) {
            aux->visibility = 0;
        } else {
            aux->visibility = 0x1f;
        }
        aux->screenX = (fx32)(tipX > 0 ? 0.5f + (float)(tipX << 12) : (float)(tipX << 12) - 0.5f);
        aux->screenY = (fx32)(tipY > 0 ? 0.5f + (float)(tipY << 12) : (float)(tipY << 12) - 0.5f);
    }
}