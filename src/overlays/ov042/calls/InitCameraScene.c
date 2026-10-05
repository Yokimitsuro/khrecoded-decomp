#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    void *func;
    int arg;
} Callback;

typedef struct {
    u8 _0[0xc0];
    u8 kind;
    u8 _c1[0xf];
} ColliderModel;

typedef struct {
    u8 _0[0xd];
    u8 active;
    u8 _e[6];
    u8 *group;
    u8 _18[0xc];
    ColliderModel *model;
    u8 _28[0x18];
    int priority;
    u8 _44[0x24];
    int unk_68;
    int id;
    Callback filter;
    Callback facing;
    Callback extra;
} Collider;

typedef struct {
    u8 _0[0xc];
    fx32 nearClip;
    fx32 farClip;
    VecFx32 eye;
    VecFx32 target;
    u8 _2c[0x14];
    int mode;
    u8 _44[0x44];
    VecFx32 goalTarget;
    VecFx32 goalEye;
    VecFx32 liveEye;
    VecFx32 baseEye;
    int unk_b8;
    u8 _bc[0x6c];
    VecFx32 shake;
    u8 _134[0x10];
    int unk_144;
    u8 _148[0x54];
    ColliderModel models[3];
    Collider colliders[3];
    u8 group;
} CameraScene;

typedef struct {
    u8 _0[0x64];
    VecFx32 target;
    VecFx32 eye;
} CameraState;

typedef struct {
    u8 _0[4];
    void **world;
} SceneRoot;

typedef void *(*SceneFunc)(void);

extern CameraState *data_ov042_020be5e0;
extern VecFx32 data_0205344c;
extern void InitCameraState(void);
extern void LoadDefaultProjectionValues(void *camera);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SetCameraGoalTarget(const VecFx32 *pos);
extern BOOL InitCollisionObject(void *object, u16 groupMask, s32 ownerId);
extern void func_ov042_020bd5bc(int extent);
extern void OffsetCameraColliders(const VecFx32 *delta);
extern SceneRoot *GetActorRegistry(void);
extern void QuadTree_InsertObject(void *world, void *object);
extern BOOL IsHitEntryAccepted(int unused, void *entry);
extern BOOL IsTargetFacing(int unused, void *entry);
extern void *func_ov042_020bde40(void);

static inline void SetupCollider(Collider *collider, int id) {
    Callback extra;
    Callback facing;
    Callback filter;
    collider->active = 1;
    collider->id = id;
    collider->unk_68 = 0;
    filter.func = IsHitEntryAccepted;
    filter.arg = 0;
    collider->filter = filter;
    facing.func = IsTargetFacing;
    facing.arg = 0;
    collider->facing = facing;
    extra.func = NULL;
    extra.arg = 0;
    collider->extra = extra;
}

SceneFunc InitCameraScene(int unused, CameraScene *camera) {
    VecFx32 offsetCopy;
    VecFx32 goalCopy;
    VecFx32 deltaCopy;
    VecFx32 offset;
    VecFx32 eye;
    VecFx32 goal;
    VecFx32 delta;
    SceneRoot *root;

    data_ov042_020be5e0 = (CameraState *)camera;
    InitCameraState();
    LoadDefaultProjectionValues(camera);
    data_ov042_020be5e0->target = camera->target;
    offset.x = 0;
    offset.y = 0;
    offset.z = -0x5000;
    offsetCopy = offset;
    VEC_Add(&data_ov042_020be5e0->target, &offsetCopy, &eye);
    camera->eye = eye;
    data_ov042_020be5e0->eye = camera->eye;
    camera->farClip = 0x64000;
    camera->nearClip = 0x800;
    goal.x = 0;
    goal.y = 0x4000;
    goal.z = 0x5000;
    goalCopy = goal;
    SetCameraGoalTarget(&goalCopy);
    camera->goalTarget = data_ov042_020be5e0->target;
    camera->goalEye = data_ov042_020be5e0->eye;
    camera->liveEye = data_ov042_020be5e0->eye;
    camera->baseEye = data_ov042_020be5e0->eye;
    camera->unk_b8 = -1;
    camera->unk_144 = 0;
    camera->shake = data_0205344c;
    InitCollisionObject(&camera->colliders[0], 0, 0);
    InitCollisionObject(&camera->colliders[1], 0, 0);
    InitCollisionObject(&camera->colliders[2], 0, 0);
    camera->colliders[0].priority = 5;
    camera->colliders[1].priority = 5;
    camera->colliders[2].priority = 5;
    camera->models[0].kind = 4;
    camera->models[1].kind = camera->models[0].kind;
    camera->models[2].kind = camera->models[1].kind;
    camera->colliders[0].model = &camera->models[0];
    camera->colliders[1].model = &camera->models[1];
    camera->colliders[2].model = &camera->models[2];
    func_ov042_020bd5bc(0x5000);
    delta.x = 0xcd;
    delta.y = 0;
    delta.z = 0;
    deltaCopy = delta;
    OffsetCameraColliders(&deltaCopy);
    SetupCollider(&camera->colliders[0], 3);
    SetupCollider(&camera->colliders[1], 4);
    SetupCollider(&camera->colliders[2], 5);
    camera->group = 5;
    camera->colliders[0].group = &camera->group;
    camera->colliders[1].group = &camera->group;
    camera->colliders[2].group = &camera->group;
    if (camera->mode == 1) {
        root = GetActorRegistry();
        QuadTree_InsertObject(*root->world, &camera->colliders[0]);
        QuadTree_InsertObject(*root->world, &camera->colliders[1]);
        QuadTree_InsertObject(*root->world, &camera->colliders[2]);
    }
    return func_ov042_020bde40;
}
