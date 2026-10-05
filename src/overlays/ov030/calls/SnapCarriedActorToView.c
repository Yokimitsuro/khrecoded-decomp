#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct {
    void *callback;
    void *owner;
} CollisionFilter;

typedef struct {
    u8 pad_00[0x50];
    CollisionFilter filter;
    u8 pad_58[8];
} CollisionQuery;

typedef struct {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct {
    u8 pad_00[0x14];
    VecFx32 target;
} SubModeView;

typedef struct {
    u8 pad_00[8];
    fx32 height;
} CameraRig;

typedef struct {
    u8 pad_00[4];
    VecFx32 velocity;
} CarryMotion;

typedef struct CarriedActor CarriedActor;

struct CarriedActor {
    u8 pad_000[0x1fc];
    void (*onLand)(CarriedActor *actor, fx32 value);
    u8 pad_200[0x230 - 0x200];
    void *owner;
    u8 pad_234[0x75c - 0x234];
    s32 motionKind;
    u8 pad_760[0x768 - 0x760];
    s32 motionActive;
    u8 pad_76c[0x9ac - 0x76c];
    u64 flags;
};

extern SubModeView *func_ov021_020af614(void);
extern CameraRig *func_ov042_020bd5b0(void);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_0203ad28(CollisionShape *shape, CollisionSphere *sphere, const VecFx32 *center, fx32 radius);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *owner, u8 kind, u8 unk3C, u8 unk3D, CollisionShape *shape, QueryWorkspace *workspace, s32 unk44);
extern void *SweepWorldCollision(CollisionQuery *query);
extern VecFx32 GetShapeCenter(const CollisionShape *shape);
extern void Obj_SetPosition(void *entity, const VecFx32 *position);
extern void AreMeshEntriesClear(void);

void SnapCarriedActorToView(CarriedActor *actor, CarryMotion *motion)
{
    CollisionQuery query;
    QueryWorkspace workspace;
    CollisionQuery setup;
    VecFx32 pos;
    CollisionSphere sphere;
    CollisionShape shapeCopy;
    VecFx32 hitPos;
    VecFx32 diff;
    CollisionShape shape;
    VecFx32 center;
    CollisionFilter filter;
    SubModeView *view = func_ov021_020af614();
    CameraRig *rig = func_ov042_020bd5b0();

    actor->flags |= 1;
    pos = view->target;
    pos.y += rig->height - 0x3000;
    VEC_Add(&pos, &motion->velocity, &pos);
    func_0203ad28(&shape, &sphere, &pos, 0xdcd);
    shapeCopy = shape;
    CollisionQuery_Init(&setup, 1, NULL, 7, 0, 0, &shapeCopy, &workspace, 0);
    query = setup;
    filter.callback = AreMeshEntriesClear;
    filter.owner = actor->owner;
    query.filter = filter;
    if (SweepWorldCollision(&query)) {
        center = GetShapeCenter(&shapeCopy);
        hitPos = center;
        VEC_Subtract(&hitPos, &pos, &diff);
        VEC_Add(&diff, &motion->velocity, &motion->velocity);
        pos = hitPos;
    }
    Obj_SetPosition(actor->owner, &pos);
    if (actor->motionActive != 0 && actor->motionKind == 0xc && actor->onLand != NULL) {
        actor->onLand(actor, 0xf000);
    }
}
