#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 center;
    fx32 radius;
} Sphere;

typedef struct {
    Sphere *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    SweptShape shape;
    void *arg;
    u8 pad_48[0x60 - 0x48];
} HitQuery;

typedef struct {
    s32 power;
    u8 pad_04[8];
    fx32 range;
    u8 pad_10[2];
    u8 element;
    u8 pad_13[0x24 - 0x13];
    u16 flags;
    u8 pad_26[2];
} HitResult;

typedef struct {
    u32 flags;
    int side;
    int kind;
    u8 pad_0c[0x18 - 0xc];
    u16 recordId;
    u8 pad_1a[0xd4 - 0x1a];
    int state;
    int combo;
} HitScan;

typedef struct GrabWork GrabWork;

typedef struct {
    s32 timer;
    GrabWork *owner;
    s32 active;
} GrabSlot;

struct GrabWork {
    u8 pad_00[0x84];
    GrabSlot slots[8];
    s16 targetIds[8];
    VecFx32 center;
    s32 unk_100;
    s32 count;
    s32 state;
};

typedef struct {
    u8 pad_00[0xbc];
    VecFx32 position;
} EntryInfo;

typedef struct {
    u8 pad_000[0x230];
    u8 *anim;
    u8 pad_234[0x9b4 - 0x234];
    u8 player;
    u8 pad_9b5[0x1078 - 0x9b5];
    GrabWork *work;
} GrabActor;

extern s16 data_02053580[];
extern const VecFx32 data_0205344c;

extern EntryInfo *GetBoundedEntryField(int index);
extern u16 GetLinkedAngleOffset(GrabActor *actor);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern int Anim_GetFrame(void *anim, int channel);
extern void ZeroBytes0x28(HitResult *result);
extern void InitRecord60(HitQuery *query);
extern void func_0203ad28(CollisionShape *out, Sphere *storage, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void ZeroAndSetField0xd4(HitScan *scan);
extern BOOL StepHitScan(int player, HitQuery *query, HitResult *result, HitScan *scan);
extern void StageRecord_SetCallback(u32 id, u32 callback, u32 userData);
extern void PullActorTowardSource(void);
extern void func_ov056_020d3418(GrabActor *actor);

void UpdateGrabSweepHits(GrabActor *actor)
{
    GrabWork *work = actor->work;
    EntryInfo *info = GetBoundedEntryField(actor->player);
    VecFx32 pos;
    VecFx32 dir;
    int index;
    int i;

    index = GetLinkedAngleOffset(actor) >> 4;
    dir.x = -data_02053580[index];
    dir.z = -data_02053580[(0x400 - index) & 0xfff];
    dir.y = 0;
    VEC_MultAdd(0x14cd, &dir, &info->position, &pos);
    pos.y += 0x119a;
    work->center = pos;

    switch (work->state) {
    case 0:
    default:
        for (i = 0; i < 8; i++) {
            work->slots[i].active = 0;
            work->targetIds[i] = -1;
        }
        work->count = 0;
        work->state = 1;
    case 1:
        if (Anim_GetFrame(actor->anim + 4, 0) < 0xa000) {
            break;
        }
        work->state = 2;
    case 2:
        if (work->count < 8) {
            GrabSlot *slot;
            HitScan *cur;
            HitQuery query;
            HitScan scan;
            SweptShape swept;
            Sphere sphere;
            HitResult hit;

            ZeroBytes0x28(&hit);
            hit.element = 9;
            hit.power = 0;
            hit.range = 0x64000;
            hit.flags |= 0x100;
            hit.flags |= 0x400;
            InitRecord60(&query);
            func_0203ad28(&swept.shape, &sphere, &work->center, 0x5000);
            swept.delta = data_0205344c;
            OffsetBoxByDelta(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
            query.shape = swept;
            query.arg = work->targetIds;
            cur = &scan;
            ZeroAndSetField0xd4(cur);
            cur->state = 5;
            while (StepHitScan(actor->player, &query, &hit, cur)) {
                if (cur->kind == 4) {
                    slot = &work->slots[work->count];
                    slot->timer = 0;
                    slot->owner = work;
                    slot->active = 1;
                    StageRecord_SetCallback(cur->recordId, (u32)PullActorTowardSource, (u32)slot);
                    if (++work->count >= 8) {
                        break;
                    }
                }
            }
        }
        work->state = 3;
    case 3:
        if (Anim_GetFrame(actor->anim + 4, 0) < 0x24000) {
            break;
        }
        work->state = 4;
    case 4:
        for (i = 0; i < 8; i++) {
            work->slots[i].active = 0;
        }
        work->state = 5;
    case 5:
        break;
    }
    func_ov056_020d3418(actor);
}
