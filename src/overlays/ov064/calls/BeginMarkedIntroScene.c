#include "nitro/types.h"

typedef struct {
    u8 id;
    u8 pad_01[0x17];
    void *user;
    u8 pad_1c[8];
    u8 hidden;
    u8 layer;
    u8 pad_26[2];
    u16 soundId;
    u16 delay;
} MarkerRequest;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x1f8];
    void (*playMotion)(Actor *actor, int motion, int blend);
    u8 pad_1fc[0x6cc - 0x1fc];
    u8 modelUser[4];
    u8 pad_6d0[0x9ac - 0x6d0];
    u64 flags;
    u8 player;
};

typedef struct {
    u8 pad_00[0x14];
    int playerIndex;
} SceneOwner;

typedef struct {
    u8 pad_00[8];
    s32 soundId;
    u8 pad_0c[0x30];
    s32 result;
    s32 motionBase;
    u8 started;
    u8 pad_45[3];
    s32 timer;
    u8 pad_4c[0x10];
    s16 groupId;
    u8 pad_5e[6];
    s32 markerSlot;
    u8 pad_68[4];
    void *cameraPath;
} SceneTask;

extern Actor *GetBoundedEntryField(int index);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern void UpdateFacingTowardTarget(Actor *actor, BOOL useEntry);
extern void func_ov046_020c2f64(void *path);

s32 BeginMarkedIntroScene(SceneOwner *owner, SceneTask *task, u32 *errorCode)
{
    Actor *actor = GetBoundedEntryField(owner->playerIndex);
    MarkerRequest request;
    int motion;

    task->started = 0;
    task->timer = 0;
    ResetAnimationTrackState(&request);
    request.id = actor->player;
    request.layer = 2;
    request.hidden = 0;
    request.user = actor->modelUser;
    request.soundId = task->soundId;
    request.delay = 0;
    task->markerSlot = func_ov021_020a8cc0(&request, task->groupId);
    UpdateFacingTowardTarget(actor, FALSE);
    motion = task->motionBase + 0x2d;
    if (actor->playMotion != NULL) {
        actor->playMotion(actor, motion, -1);
    }
    actor->flags |= 0x40;
    func_ov046_020c2f64(task->cameraPath);
    *errorCode = 0x18;
    return task->result;
}
