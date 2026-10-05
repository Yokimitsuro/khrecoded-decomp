#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef struct SlotEntry SlotEntry;

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    u32 kind;
    Box box;
    int index;
    VecFx32 delta;
    Box sweptBox;
} HitVolume;

typedef struct {
    HitVolume volume;
    u32 owner;
    VecFx32 motion;
    fx32 scale;
    u16 angle;
    u8 pad_5a[2];
    int target;
} HitAttack;

typedef struct {
    u8 pad_00[0x14];
    int ignoreGuard;
    int knockbackY;
    int knockbackXZ;
    int canHit;
    u8 pad_24[4];
} HitOptions;

typedef struct {
    u32 flags;
    int reaction;
    int type;
    u8 pad_0c[0xd0];
} HitScan;

typedef struct {
    s8 slot;
    u8 pad_01[3];
    fx32 radius;
    u8 allowCounter;
} HitShape;

typedef struct {
    u8 pad_00[0xc];
    int startFrame;
    int endFrame;
    int knockbackXZ;
    int knockbackY;
    u8 pad_1c[8];
    HitShape shape;
} HitEntry;

typedef void (*HitCallback)(Actor *actor, HitScan *scan, SlotEntry *entry);

struct SlotEntry {
    HitCallback onHit;
    u8 pad_04[8];
    VecFx32 pos;
    u16 primary : 1;
    u16 useEntryPos : 1;
    u16 noSpark : 1;
    u16 landed : 1;
    u16 reserved4 : 1;
    u16 linked : 1;
};

typedef struct {
    u8 data[0x230];
} SlotTable;

struct Actor {
    u8 pad_0000[0x760];
    int frame;
    u8 pad_0764[0x9b4 - 0x764];
    u8 player;
    u8 pad_09b5[0xb68 - 0x9b5];
    SlotTable slotTables[2];
};

extern BOOL func_ov021_020a9d24(SlotTable *table);
extern u16 GetLinkedAngleOffset(Actor *actor);
extern void InitRecord60(HitAttack *attack);
extern void GetAttachmentWorldPosition(VecFx32 *out, Actor *actor, int slot);
extern void func_0203ad28(HitVolume *volume, int *bounds, VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void ZeroBytes0x28(void *obj);
extern void func_ov052_020d1880(HitOptions *out, Actor *actor, HitEntry *hit, SlotEntry *entry);
extern void ZeroAndSetField0xd4(void *obj);
extern BOOL StepHitScan(int type, HitAttack *attack, HitOptions *options, HitScan *scan);
extern void SpawnHitSparkMarker(Actor *actor, HitScan *scan, SlotEntry *entry, VecFx32 *target);

BOOL RunVolumeHitScan(Actor *actor, HitEntry *hit, u32 owner, SlotEntry *entry)
{
    HitAttack attack;
    HitScan scan;
    HitVolume volume;
    HitOptions options;
    int bounds[4];
    VecFx32 center;
    u16 angle;
    BOOL landed;
    HitShape *shape = &hit->shape;
    HitScan *scanPtr;
    int knockbackY;
    int knockbackXZ;

    if (hit->startFrame > actor->frame || hit->endFrame <= actor->frame) {
        return FALSE;
    }
    if (shape->slot < 2 && !func_ov021_020a9d24(&actor->slotTables[shape->slot])) {
        return FALSE;
    }
    angle = GetLinkedAngleOffset(actor);
    InitRecord60(&attack);
    attack.scale = 0x1000;
    attack.owner = owner;
    attack.target = 0;
    attack.angle = angle;
    if (!entry->useEntryPos) {
        GetAttachmentWorldPosition(&center, actor, shape->slot);
    } else {
        center = entry->pos;
    }
    func_0203ad28(&volume, bounds, &center, shape->radius);
    volume.delta = attack.motion;
    OffsetBoxByDelta(&volume.box, &volume.sweptBox, &volume.delta);
    attack.volume = volume;
    ZeroBytes0x28(&options);
    func_ov052_020d1880(&options, actor, hit, entry);
    knockbackXZ = hit->knockbackXZ;
    knockbackY = hit->knockbackY;
    options.ignoreGuard = 0;
    options.knockbackY = knockbackY;
    options.knockbackXZ = knockbackXZ;
    options.canHit = 1;
    scanPtr = &scan;
    ZeroAndSetField0xd4(scanPtr);
    while (StepHitScan(actor->player, &attack, &options, scanPtr)) {
        landed = FALSE;
        switch (scanPtr->type) {
        case 2:
        case 3:
        case 4:
            landed = TRUE;
            if (!(scanPtr->flags & 1) && !(scanPtr->flags & 0x20)) {
                entry->primary = 1;
            }
            if (scanPtr->flags & 0x80) {
                entry->linked = 1;
            }
            break;
        case 1:
            if (!(scanPtr->flags & 1)) {
                landed = TRUE;
                if (scanPtr->reaction == 2 && shape->allowCounter == 0) {
                    landed = FALSE;
                }
            }
            break;
        }
        if (landed) {
            entry->landed = 1;
            if (!entry->noSpark) {
                SpawnHitSparkMarker(actor, scanPtr, entry, &center);
            }
            if (entry->onHit != NULL) {
                entry->onHit(actor, scanPtr, entry);
            }
        }
    }
    return FALSE;
}
