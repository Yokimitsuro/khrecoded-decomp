#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweepShape;

typedef struct {
    u32 data[0x18];
} CollisionQuery;

typedef struct {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct {
    u8 kind;
    u8 group;
    u8 index;
} LinkInfo;

typedef struct {
    u8 pad_000[0x194];
    LinkInfo link;
} LinkOwner;

typedef struct {
    u8 pad_00[0x14];
    LinkOwner *owner;
} LinkHolder;

typedef struct {
    LinkHolder *holder;
    s32 mode;
} LinkQuery;

typedef struct {
    u8 pad_00[0xac];
    fx32 floorHeight;
} SweepActor;

typedef struct {
    VecFx32 *position;
} PositionRef;

extern u32 func_ov001_0207f060(u32 group, u32 index);
extern VecFx32 *func_ov001_0207f838(u32 entry);
extern u8 *func_ov001_0208724c(u32 group, u32 index);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void InitCylinderShape(CollisionShape *shape, CollisionCylinder *cylinder, const VecFx32 *start, const VecFx32 *end,
                                       const VecFx32 *direction, fx32 length, fx32 radius);
extern void OffsetBoxByDelta(const s32 *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, SweepActor *actor, u8 kind, u8 unk3C, u8 unk3D, SweepShape *shape, QueryWorkspace *workspace, s32 unk44);
extern void *SweepWorldCollisionPreserveState(CollisionQuery *query);

BOOL CheckLinkedTargetClearance(LinkQuery *link, u32 unused, SweepActor **actorRef, PositionRef *posRef)
{
    BOOL result = TRUE;
    SweepActor *actor = *actorRef;

    if (link->mode == 4) {
        VecFx32 *target = NULL;
        LinkInfo *info = &link->holder->owner->link;
        switch (info->kind) {
        case 4: {
            u8 *node = func_ov001_0208724c(info->group, info->index);
            if (node != NULL) {
                target = (VecFx32 *)(node + 0x38);
            }
            break;
        }
        case 2: {
            u32 entry = func_ov001_0207f060(info->group, info->index);
            if (entry != 0) {
                target = func_ov001_0207f838(entry);
            }
            break;
        }
        }
        if (target != NULL) {
            CollisionQuery query;
            QueryWorkspace workspace;
            SweepShape sweepCopy;
            SweepShape sweep;
            CollisionQuery setup;
            VecFx32 start;
            VecFx32 end;
            VecFx32 delta;
            VecFx32 hitEnd;
            CollisionCylinder cylinder;
            VecFx32 direction;
            VecFx32 diff;
            CollisionShape shape;

            start = *posRef->position;
            start.y = target->y - 0x19a;
            end = start;
            end.y = end.y - 0x19a;
            delta.x = 0;
            delta.y = -0xa000;
            delta.z = 0;
            VEC_Subtract(&end, &start, &diff);
            direction = diff;
            InitCylinderShape(&shape, &cylinder, &start, &end, &direction, func_01ffaff4(&direction, &direction), 0x333);
            sweep.shape = shape;
            sweep.delta = delta;
            OffsetBoxByDelta(sweep.shape.bounds, &sweep.sweptBounds, &sweep.delta);
            sweepCopy = sweep;
            CollisionQuery_Init(&setup, 0, actor, 9, 1, 1, &sweepCopy, &workspace, 0);
            query = setup;
            if (SweepWorldCollisionPreserveState(&query)) {
                hitEnd = ((CollisionCylinder *)sweepCopy.shape.data)->end;
                if (hitEnd.y > actor->floorHeight && target->y >= hitEnd.y + 0x1800) {
                    result = FALSE;
                }
            }
        }
    }
    return result;
}
