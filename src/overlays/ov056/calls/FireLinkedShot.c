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
    u8 pad_10[0x74];
    void *owner;
} ShotDef;

typedef struct {
    u8 pad_000[0x1078];
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

extern const VecFx32 data_0205344c;
extern s32 GetLinkedAngleOffset(ShotActor *actor);
extern VecFx32 *func_ov052_020ceb74(ShotActor *actor);
extern void ZeroBytes0x40(ShotDesc *desc);
extern void RotateOffsetAroundY(VecFx32 *out, const VecFx32 *origin, u16 angle, const VecFx32 *offset);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern ShotProjectile *TryConsumeLimitedUse(void *owner, ShotDesc *desc);
extern u32 SpawnSoundSlot(u32 owner, u32 kind, VecFx32 *position, u32 flags);

BOOL FireLinkedShot(ShotActor *actor, void *arg, ShotPattern *pattern, ShotEvent *event)
{
    ShotAim *aim = &pattern->aim;
    int angle;
    ShotDef *shot;
    ShotProjectile *projectile;
    ShotDesc desc;
    VecFx32 direction;

    angle = (u16)(GetLinkedAngleOffset(actor) + 0x8000);
    shot = actor->shot;
    ZeroBytes0x40(&desc);
    RotateOffsetAroundY(&desc.position, func_ov052_020ceb74(actor), angle, &aim->offset);
    RotateOffsetAroundY(&direction, &data_0205344c, angle, &aim->direction);
    desc.direction = direction;
    func_01ffaff4(&desc.direction, &desc.direction);
    desc.flags = 0;
    if (shot->kind == 4) {
        desc.flags |= 2;
    }
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
    projectile = TryConsumeLimitedUse(shot->owner, &desc);
    if (projectile != NULL) {
        projectile->shot = shot;
    }
    if (shot->id == 0x8f && projectile != NULL) {
        SpawnSoundSlot(shot->soundId, 0, &desc.position, 5);
    }
    aim->fired = TRUE;
    return FALSE;
}
