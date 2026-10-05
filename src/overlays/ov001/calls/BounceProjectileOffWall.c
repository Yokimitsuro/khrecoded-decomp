#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct CollisionShape {
    void *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    u8 data[0x28];
} ShapeStorage;

typedef struct {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct {
    u32 words[0x18];
} CollisionQuery;

typedef struct ContactRef {
    void *owner;
    s32 type;
} ContactRef;

typedef struct ProjectileBody {
    u8 pad_00[0x10];
    u8 anchor[1];
} ProjectileBody;

typedef struct Projectile {
    u8 pad_00[0xc];
    ProjectileBody *body;
    u8 pad_10[4];
    void (*update)(struct Projectile *self);
    u8 pad_18[0x40 - 0x18];
    VecFx32 position;
    u8 pad_4c[0x58 - 0x4c];
    s32 state;
    u8 pad_5c[0x70 - 0x5c];
    VecFx32 drift;
    VecFx32 velocity;
    s32 heading;
    u8 pad_8c[4];
    s32 baseAngle;
    s32 turn;
    u8 pad_98[4];
    s32 timer;
} Projectile;

extern const VecFx32 data_0205344c;
extern const s16 data_02053580[];
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern CollisionShape func_0203ade0(ShapeStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void NegateVecFx32(VecFx32 *vec);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void SetShapePosition(CollisionShape *shape, const VecFx32 *position);
extern BOOL SweepWorldCollisionPreserveState(CollisionQuery *query);
extern int FX_Atan2(fx32 y, fx32 x);
extern void SpawnSoundSlot(int soundId, int mode, const VecFx32 *position, int flags);
extern int FX_Mul(int left, int right);
extern void UpdateSpawnerRise(Projectile *self);

#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (b) + (FX32_ONE >> 1)) >> 12))

static inline void BuildSegmentShape(CollisionShape *shape, ShapeStorage *storage, const VecFx32 *position, const VecFx32 *top)
{
    VecFx32 axis;
    VecFx32 delta;
    fx32 length;
    VEC_Subtract(top, position, &delta);
    axis = delta;
    length = func_01ffaff4(&axis, &axis);
    *shape = func_0203ade0(storage, position, top, &axis, length);
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

static inline VecFx32 AddVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Add(a, b, &result);
    return result;
}

static inline VecFx32 CrossProduct(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    result.x = -FX_MUL(a->z, b->y);
    result.y = 0;
    result.z = FX_MUL(a->x, b->y);
    return result;
}

void BounceProjectileOffWall(ContactRef *contact, const VecFx32 *normal, Projectile *projectile)
{
    BOOL bounce = TRUE;

    if (contact->type == 2 && VEC_DotProduct(&projectile->velocity, normal) < -0xb50 && projectile->state == 1) {
        QueryWorkspace workspace;
        CollisionQuery sweep;
        CollisionQuery query;
        ShapeStorage storage;
        CollisionShape shape;
        VecFx32 side;
        VecFx32 top;
        VecFx32 up;
        VecFx32 position;
        u8 i;

        projectile->drift = MakeVec(0, 0x266, 0);
        projectile->state = 2;
        projectile->update = UpdateSpawnerRise;
        projectile->timer = 0;
        top = MakeVec(0, -0x3000, 0);
        BuildSegmentShape(&shape, &storage, &data_0205344c, &top);
        CollisionQuery_Init(&query, 0, projectile->body->anchor, 1, 2, 0, &shape, &workspace, NULL);
        sweep = query;
        up = MakeVec(0, FX32_ONE, 0);
        side = CrossProduct(normal, &up);
        if (side.z < 0) {
            NegateVecFx32(&side);
        }
        func_01ffaff4(&side, &side);
        ScaleVecFx32InPlace(&side, 0x3e67);
        for (i = 0; i < 2; i++) {
            if (i == 1) {
                NegateVecFx32(&side);
            }
            position = AddVec(&projectile->position, &side);
            SetShapePosition(&shape, &position);
            if (SweepWorldCollisionPreserveState(&sweep)) {
                int index;

                VEC_Normalize(&side, &projectile->velocity);
                projectile->baseAngle = projectile->heading;
                projectile->turn = FX_Atan2(projectile->velocity.z, projectile->velocity.x);
                projectile->turn = projectile->turn - projectile->baseAngle;
                index = (s32)((((s64)projectile->turn << 16) / 0x6488) & 0xffff) >> 4;
                projectile->turn = FX_Atan2(data_02053580[index], data_02053580[(0x400 - index) & 0xfff]);
                projectile->turn = projectile->turn + projectile->baseAngle;
                SpawnSoundSlot(0x1a1, 1, &projectile->position, 0);
                break;
            }
        }
        bounce = FALSE;
    }
    if (bounce) {
        fx32 dot = VEC_DotProduct(&projectile->drift, normal);
        VEC_MultAdd(-(dot + FX_Mul(dot, 0xccd)), normal, &projectile->drift, &projectile->drift);
    }
}





