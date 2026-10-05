#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    u8 data[0x2c];
} CylinderStorage;

typedef struct {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct {
    void (*func)(void);
    void *arg;
} QueryCallback;

typedef struct {
    u32 words[0x12];
    QueryCallback filter;
    QueryCallback callback;
    u32 tail[2];
} CollisionQuery;

typedef union {
    u32 raw;
    struct {
        u32 matchFlag : 1;
        u32 enabled : 1;
    } bits;
} SweepFilterArg;

typedef struct {
    VecFx32 position;
    VecFx32 direction;
    s32 stats[3];
    s32 pad_24;
    s32 power;
    s32 flags;
    u32 subKind;
    u32 kind;
    s32 count;
    s32 pad_3c;
} ShotDesc;

typedef struct {
    u8 id;
    u8 pad_01[0x23];
    u8 hidden;
    u8 layer;
    u8 pad_26[2];
    u16 soundId;
    u16 delay;
} MarkerRequest;

typedef struct {
    u8 pad_00[8];
    s32 soundId;
    u8 pad_0c[0x38];
    s32 waveCount;
    BOOL markerPlaced;
    fx32 waveTimer;
    s16 groupA;
    s16 groupB;
    u8 pad_54[4];
    void *shotOwner;
} SlamTask;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x1fc];
    void (*onLand)(Actor *actor, int frame);
    u8 pad_200[0x228 - 0x200];
    BOOL (*getFootPosition)(Actor *actor, VecFx32 *out);
    u8 pad_22c[0x234 - 0x22c];
    u32 stateFlags;
    u8 pad_238[0x760 - 0x238];
    s32 frame;
    u8 pad_764[4];
    s32 finished;
    u8 pad_76c[0x9b4 - 0x76c];
    u8 player;
    u8 pad_9b5[0x9c8 - 0x9b5];
    fx32 posX;
    fx32 posY;
    fx32 posZ;
    u8 pad_9d4[0x9ec - 0x9d4];
    fx32 frameStep;
    u8 pad_9f0[0x1078 - 0x9f0];
    SlamTask *task;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setMode)(Actor *actor, int mode);
};

extern void func_ov052_020ce9f4(Actor *actor, VecFx32 *out);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern void func_ov021_020ab0ac(ShotDesc *desc);
extern VecFx32 *func_ov052_020ceb74(Actor *actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollisionShape InitCylinderShape(CylinderStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void *ActorRegistry_GetEntityByIndex(u16 actorId);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void *SweepWorldCollision(CollisionQuery *query);
extern void func_ov021_020a9288(void);
extern void *func_ov021_020ab0b8(void *owner, ShotDesc *desc);
extern u32 SpawnSoundSlot(u32 owner, u32 kind, VecFx32 *position, u32 flags);
extern void func_ov021_020af564(int a, int b);
extern void func_ov001_020734f8(void);
extern void SetManagerEnabled(u32 enabled);

void UpdateGroundSlamAction(Actor *actor)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    SweptShape sweptCopy;
    SweptShape swept;
    CollisionQuery cylinderQuery;
    VecFx32 delta;
    MarkerRequest request;
    ShotDesc desc;
    VecFx32 pos;
    CylinderStorage cylinder;
    VecFx32 start;
    VecFx32 end;
    VecFx32 dropDelta;
    VecFx32 cylinderAxis;
    VecFx32 cylinderDiff;
    CollisionShape cylinderShape;
    SweepFilterArg filterArg;
    QueryCallback cylinderCallback;
    u32 grounded = actor->stateFlags & 4;
    BOOL fire = FALSE;
    SlamTask *task = actor->task;
    BOOL found;
    void *target;

    if (actor->finished == 0 && actor->frame < 0x42000) {
        func_ov052_020ce9f4(actor, &delta);
        actor->posY = delta.y;
        actor->posX += delta.x;
        actor->posZ += delta.z;
    }
    if (task->markerPlaced == FALSE && actor->frame >= 0xc000) {
        ResetAnimationTrackState(&request);
        request.id = actor->player;
        request.layer = 1;
        request.hidden = 0;
        request.soundId = task->soundId;
        request.delay = 0;
        func_ov021_020a8cc0(&request, task->groupA);
        task->markerPlaced = TRUE;
    }
    if (task->waveCount == 0) {
        if (actor->frame >= 0x31000) {
            fire = TRUE;
            task->waveCount++;
            task->waveTimer = 0;
        }
    } else {
        task->waveTimer += actor->frameStep;
        if (task->waveTimer >= 0xe000) {
            if (task->waveCount < 5) {
                fire = TRUE;
            }
            task->waveCount++;
            task->waveTimer = 0;
        }
    }
    if (task->waveCount <= 5 && actor->frame >= 0x42000 && actor->onLand != NULL) {
        actor->onLand(actor, 0x34000);
    }
    if (fire) {
        func_ov021_020ab0ac(&desc);
        if (actor->getFootPosition != NULL) {
            found = actor->getFootPosition(actor, &pos);
        } else {
            found = FALSE;
        }
        if (!found) {
            pos = *func_ov052_020ceb74(actor);
        }
        start = pos;
        start.y += 0x1000;
        end = start;
        end.y -= 0x19a;
        dropDelta.x = 0;
        dropDelta.y = -0x14000;
        dropDelta.z = 0;
        VEC_Subtract(&end, &start, &cylinderDiff);
        cylinderAxis = cylinderDiff;
        cylinderShape = InitCylinderShape(&cylinder, &start, &end, &cylinderAxis, func_01ffaff4(&cylinderAxis, &cylinderAxis), 0x19a);
        swept.shape = cylinderShape;
        swept.delta = dropDelta;
        OffsetBoxByDelta(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
        sweptCopy = swept;
        target = ActorRegistry_GetEntityByIndex(actor->player);
        CollisionQuery_Init(&cylinderQuery, 0, target, 9, 1, 1, &sweptCopy, &workspace, NULL);
        sweep = cylinderQuery;
        filterArg.raw = 0;
        filterArg.bits.matchFlag = 1;
        filterArg.bits.enabled = 1;
        cylinderCallback.func = func_ov021_020a9288;
        cylinderCallback.arg = &filterArg;
        sweep.callback = cylinderCallback;
        if (SweepWorldCollision(&sweep) != NULL) {
            pos = sweptCopy.shape.data[1];
        } else {
            pos.y -= 0xa000;
        }
        desc.position = pos;
        desc.flags = 3;
        desc.stats[0] = 0x1400;
        desc.count = 1;
        desc.pad_3c = 0;
        func_ov021_020ab0b8(task->shotOwner, &desc);
        SpawnSoundSlot(task->soundId, 1, &desc.position, 0);
        func_ov021_020af564(3, 0);
        ResetAnimationTrackState(&request);
        request.id = actor->player;
        request.hidden = 0;
        request.layer = 1;
        func_ov021_020a8cc0(&request, task->groupB);
    }
    if (actor->finished == 0) {
        return;
    }
    func_ov001_020734f8();
    SetManagerEnabled(0);
    if (grounded) {
        actor->setMode(actor, 5);
    } else {
        actor->setMode(actor, 4);
    }
}
