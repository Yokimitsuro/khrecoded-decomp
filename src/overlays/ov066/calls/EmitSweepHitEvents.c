#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 minX, minY, minZ;
    fx32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 center;
    fx32 radius;
} Sphere;

typedef struct {
    Sphere *shape;
    Box bounds;
    s32 flags;
    VecFx32 delta;
    Box swept;
} ShapeQuery;

typedef struct {
    u8 pad_00[0x18];
} QueryCursor;

typedef struct {
    u8 pad_00[8];
    VecFx32 position;
    u8 pad_14[0x10];
} TargetInfo;

typedef struct {
    VecFx32 offset;
    u8 pad_0c[0x1c];
    u16 flags;
    u8 pad_2a[4];
    u16 player;
    u8 pad_30[4];
    VecFx32 origin;
    u8 pad_40[8];
} HitEvent;

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x14];
    u8 hidden;
    u8 layer;
    u8 pad_26[2];
    u16 soundId;
    u16 delay;
} MarkerRequest;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0xbc];
    VecFx32 position;
    u8 pad_0c8[0x224 - 0xc8];
    VecFx32 *(*getPosition)(Actor *actor);
    u8 pad_228[0x760 - 0x228];
    s32 frame;
    u8 pad_764[0x9b4 - 0x764];
    u8 player;
};

extern s16 data_02053580[];
extern const VecFx32 data_0205344c;
extern int func_ov052_020ceb9c(Actor *actor);
extern VecFx32 *func_ov052_020ceb74(Actor *actor);
extern void RotateOffsetAroundY(VecFx32 *out, const VecFx32 *origin, u16 angle, const VecFx32 *offset);
extern void func_0203ad28(ShapeQuery *query, Sphere *shape, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void ForwardToActiveService(void);
extern s32 func_ov001_020878c4(ShapeQuery *query, QueryCursor *cursor, u16 *outResult);
extern BOOL func_ov001_02087988(u32 id, TargetInfo *out);
extern void func_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void MI_CpuFill8(void *dst, int value, int size);
extern int DispatchStageEventArg(u32 id, HitEvent *event);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern fx32 nextRandom12(void);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern int func_ov001_0206db8c(int index);

void EmitSweepHitEvents(Actor *actor)
{
    ShapeQuery query;
    HitEvent event;
    ShapeQuery temp;
    QueryCursor cursor;
    Sphere sphere;
    VecFx32 offset;
    TargetInfo info;
    VecFx32 dir;
    MarkerRequest request;
    VecFx32 pos;
    u16 result;
    int angle;
    s32 id;
    int index;
    VecFx32 *origin;

    if (actor->frame < 0x1f000 || actor->frame >= 0x34000) {
        return;
    }
    angle = (u16)(func_ov052_020ceb9c(actor) - 0x8000);
    offset.x = 0;
    offset.y = 0;
    offset.z = 0x800;
    if (actor->getPosition != NULL) {
        origin = actor->getPosition(actor);
    } else {
        origin = &actor->position;
    }
    RotateOffsetAroundY(&offset, origin, angle, &offset);
    func_0203ad28(&temp, &sphere, &offset, 0x1800);
    temp.delta = data_0205344c;
    OffsetBoxByDelta(&temp.bounds, &temp.swept, &temp.delta);
    query = temp;
    ForwardToActiveService();
    do {
        id = func_ov001_020878c4(&query, &cursor, &result);
        if (id == 0) {
            return;
        }
        if (!func_ov001_02087988(id, &info)) {
            continue;
        }
        dir.z = 0;
        dir.y = 0;
        dir.x = 0;
        index = (u16)func_ov052_020ceb9c(actor) >> 4;
        dir.x = -data_02053580[index];
        dir.z = -data_02053580[(0x400 - index) & 0xfff];
        func_01ffafb4(0x1000, &dir, &dir);
        MI_CpuFill8(&event, 0, sizeof(HitEvent));
        event.player = actor->player;
        event.origin = *func_ov052_020ceb74(actor);
        event.offset = dir;
        event.flags |= 0x100;
        DispatchStageEventArg(id, &event);
        pos = info.position;
        ResetAnimationTrackState(&request);
        request.id = actor->player;
        request.layer = 0;
        pos.x += FX_Mul(nextRandom12() - 0x800, 0x4cd);
        pos.y += FX_Mul(nextRandom12() - 0x800, 0x4cd);
        pos.z += FX_Mul(nextRandom12() - 0x800, 0x4cd);
        request.position = pos;
        request.soundId = 0;
        request.delay = 0x21;
        request.hidden = 0;
        func_ov021_020a8cc0(&request, func_ov001_0206db8c(4));
    } while (id != 0);
}
