#include "nitro/types.h"

typedef struct {
    u8 id;
    u8 pad_01[0x11];
    u16 delay;
    u8 pad_14[0x10];
    u8 hidden;
    u8 layer;
    u8 pad_26[6];
} MarkerRequest;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x1f8];
    void (*playMotion)(Actor *actor, int motion, int blend);
    void (*setVisible)(Actor *actor, int visible);
    u8 pad_200[0x9ac - 0x200];
    u64 flags;
    u8 player;
    u8 pad_9b5[0xa51 - 0x9b5];
    u8 locked;
};

typedef struct {
    u8 pad_00[0x4c];
    u16 drawFlags;
} ModelGroup;

typedef struct {
    u8 pad_00[0x14];
    int playerIndex;
} SceneOwner;

typedef struct {
    u8 pad_00[0x3c];
    s32 result;
    u8 pad_40[0x2c];
    ModelGroup *model;
    u8 pad_70[4];
    s16 *groupId;
    u8 pad_78[8];
    s8 markerA;
    s8 markerB;
    u8 pad_82[6];
    void *cameraPath;
} SceneTask;

extern Actor *GetBoundedEntryField(int index);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern void ResetModelGroup(ModelGroup *model);
extern void UpdateFacingTowardTarget(Actor *actor, BOOL useEntry);
extern void CameraPath_Start(void *path);

s32 BeginSweepIntroScene(SceneOwner *owner, SceneTask *task, u32 *errorCode)
{
    Actor *actor = GetBoundedEntryField(owner->playerIndex);
    MarkerRequest request;
    ModelGroup *model;

    actor->flags |= 0x40;
    actor->locked = 0;
    task->markerA = -1;
    task->markerB = -1;
    ResetAnimationTrackState(&request);
    request.id = actor->player;
    request.layer = 1;
    request.delay = 0x8000;
    request.hidden = 0;
    func_ov021_020a8cc0(&request, *task->groupId);
    model = task->model;
    if (actor->playMotion != NULL) {
        actor->playMotion(actor, 0x2b, -1);
    }
    if (actor->setVisible != NULL) {
        actor->setVisible(actor, 0);
    }
    ResetModelGroup(model);
    model->drawFlags = (model->drawFlags & ~0x180) | 0x80;
    UpdateFacingTowardTarget(actor, TRUE);
    CameraPath_Start(task->cameraPath);
    *errorCode = 0x18;
    return task->result;
}
