#include "nitro/types.h"
#include "nitro/fx_types.h"

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
    u8 pad_01[3];
    VecFx32 offset;
    u8 pad_10[2];
    u16 angle;
    s32 color;
    u8 pad_18[0x10];
    s16 prevIndex;
    s16 index;
} MarkerRequest;

typedef struct {
    u8 pad_00[4];
    u8 kind;
    u8 subKind;
    u8 pad_06[2];
    s32 power;
} ShotRequest;

typedef struct {
    s32 id;
    s32 kind;
    s32 markerIndex;
    ShotRequest *request;
    u8 pad_10[0x6c];
    s16 *groupId;
    u8 pad_80;
    s8 handle;
    u8 pad_82[2];
    void *owner;
} ShotDef;

typedef struct {
    u8 pad_000[0x9b4];
    u8 markerId;
    u8 pad_9b5[0x9ec - 0x9b5];
    s32 color;
    u8 pad_9f0[0x1078 - 0x9f0];
    ShotDef *shot;
} ShotActor;

typedef struct {
    u8 pad_00[4];
    VecFx32 offset;
    VecFx32 direction;
    u8 fired : 1;
} ShotAim;

typedef struct {
    s32 stats[3];
    u8 pad_0c[0x18];
    ShotAim aim;
} ShotPattern;

typedef struct {
    u8 pad_00[0x18];
    u16 pad_bits : 7;
    u16 piercing : 1;
} ShotEvent;

typedef struct {
    u8 pad_000[0x150];
    ShotDef *shot;
} ShotProjectile;

extern const VecFx32 data_ov056_020d7f6c;
extern const VecFx32 data_0205344c;
extern s32 func_ov052_020ceb9c(ShotActor *actor);
extern VecFx32 *func_ov052_020ceb74(ShotActor *actor);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern s8 func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern void func_ov021_020ab0ac(ShotDesc *desc);
extern void func_ov021_020a9180(VecFx32 *out, const VecFx32 *origin, u16 angle, const VecFx32 *offset);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern ShotProjectile *func_ov021_020ab0b8(void *owner, ShotDesc *desc);

BOOL FireMarkedLinkedShot(ShotActor *actor, void *arg, ShotPattern *pattern, ShotEvent *event)
{
    ShotAim *aim = &pattern->aim;
    int angle;
    ShotDef *shot;
    ShotProjectile *projectile;
    VecFx32 pos;
    MarkerRequest request;
    ShotDesc desc;
    VecFx32 direction;

    angle = (u16)(func_ov052_020ceb9c(actor) + 0x8000);
    pos = data_ov056_020d7f6c;
    shot = actor->shot;
    func_ov021_020a9180(&pos, func_ov052_020ceb74(actor), angle, &pos);
    if (shot->handle == -1) {
        ResetAnimationTrackState(&request);
        request.id = actor->markerId;
        request.angle = angle;
        request.offset = pos;
        request.prevIndex = shot->markerIndex;
        request.index = 0;
        request.color = actor->color;
        shot->handle = func_ov021_020a8cc0(&request, *shot->groupId);
    }
    func_ov021_020ab0ac(&desc);
    desc.position = pos;
    func_ov021_020a9180(&direction, &data_0205344c, angle, &aim->direction);
    desc.direction = direction;
    VEC_Normalize(&desc.direction, &desc.direction);
    desc.flags = 0;
    if (event->piercing) {
        desc.flags |= 4;
    }
    desc.count = 0;
    desc.stats[0] = pattern->stats[0];
    desc.stats[1] = pattern->stats[1];
    desc.stats[2] = pattern->stats[2];
    desc.pad_3c = 0;
    desc.kind = shot->request->kind;
    desc.subKind = shot->request->subKind;
    desc.power = shot->request->power;
    projectile = func_ov021_020ab0b8(shot->owner, &desc);
    if (projectile != NULL) {
        projectile->shot = shot;
    }
    aim->fired = TRUE;
    return FALSE;
}
