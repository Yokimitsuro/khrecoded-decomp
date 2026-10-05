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
    u8 pad_00[4];
    u8 kind;
    u8 subKind;
    u8 pad_06[2];
    s32 power;
} ShotRequest;

typedef struct {
    s32 id;
    s32 kind;
    s32 soundId;
    ShotRequest *request;
    u8 pad_10[0x64];
    s16 *groupId;
    u8 pad_78[8];
    s8 markerSlot;
    u8 pad_81[3];
    void *owner;
    u8 pad_88[4];
    VecFx32 markerPos;
    u16 markerAngle;
} ShotDef;

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[2];
    u16 angle;
    u8 pad_14[0x14];
    u16 soundId;
    u16 delay;
} MarkerRequest;

typedef struct {
    u8 pad_000[0x9b4];
    u8 player;
    u8 pad_9b5[0x1078 - 0x9b5];
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
    u8 pad_0c[0x16];
    u8 pad_bits : 3;
    u8 mirrored : 1;
    u8 pad_23;
    ShotAim aim;
} ShotPattern;

typedef struct {
    u8 pad_000[0x150];
    ShotDef *shot;
} ShotProjectile;

extern const VecFx32 data_0205344c;
extern s32 GetLinkedAngleOffset(ShotActor *actor);
extern VecFx32 *func_ov052_020ceb74(ShotActor *actor);
extern void ZeroBytes0x40(ShotDesc *desc);
extern void RotateOffsetAroundY(VecFx32 *out, const VecFx32 *origin, u16 angle, const VecFx32 *offset);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern ShotProjectile *TryConsumeLimitedUse(void *owner, ShotDesc *desc);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);

BOOL FireMarkedGroupShot(ShotActor *actor, void *arg, ShotPattern *pattern)
{
    ShotAim *aim = &pattern->aim;
    int angle;
    ShotDef *shot;
    ShotProjectile *projectile;
    VecFx32 origin;
    MarkerRequest request;
    ShotDesc desc;
    VecFx32 direction;

    angle = (u16)(GetLinkedAngleOffset(actor) + 0x8000);
    shot = actor->shot;
    RotateOffsetAroundY(&origin, func_ov052_020ceb74(actor), angle, &aim->offset);
    if (shot->markerSlot == -1) {
        ResetAnimationTrackState(&request);
        request.id = actor->player;
        request.angle = angle;
        request.position = origin;
        request.soundId = shot->soundId;
        request.delay = 0;
        shot->markerSlot = func_ov021_020a8cc0(&request, *shot->groupId);
        shot->markerPos = origin;
        shot->markerAngle = angle;
    }
    ZeroBytes0x40(&desc);
    desc.position = shot->markerPos;
    RotateOffsetAroundY(&direction, &data_0205344c, shot->markerAngle, &aim->direction);
    desc.direction = direction;
    func_01ffaff4(&desc.direction, &desc.direction);
    desc.flags = 2;
    if (pattern->mirrored) {
        desc.flags |= 1;
    }
    desc.count = 1;
    desc.stats[0] = pattern->stats[0];
    desc.stats[1] = pattern->stats[1];
    desc.pad_3c = 0;
    desc.kind = shot->request->kind;
    desc.subKind = shot->request->subKind;
    desc.power = shot->request->power;
    projectile = TryConsumeLimitedUse(shot->owner, &desc);
    if (projectile != NULL) {
        projectile->shot = shot;
    }
    aim->fired = TRUE;
    return FALSE;
}
