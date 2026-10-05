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
    int arg;
    VecFx32 delta;
    fx32 scale;
    s16 angle;
    VecFx32 *anchor;
} HitQuery;

typedef struct {
    u8 pad_00[0x14];
    int power;
    int stun;
    int basePower;
    int bonus;
    u16 guarded : 1;
} HitResult;

typedef struct {
    u32 flags;
    int side;
    int kind;
    u8 pad_0c[0xc8];
    int state;
    int combo;
} HitScan;

typedef struct {
    VecFx32 offset;
    fx32 radius;
    s16 scale;
    u8 pad_12;
    u8 scaleMask : 5;
    u8 useAnchor : 1;
} AttackShape;

typedef struct {
    u8 pad_00[0xc];
    int startFrame;
    int endFrame;
    int power;
    int stun;
    u8 pad_1c[8];
    AttackShape shape;
} AttackData;

typedef struct Actor Actor;
typedef struct SlotEntry SlotEntry;
typedef void (*HitCallback)(Actor *actor, HitScan *scan, SlotEntry *entry);
typedef int (*StateSetter)(Actor *actor, int state);

struct SlotEntry {
    HitCallback onHit;
    u8 pad_04[8];
    VecFx32 pos;
    u16 hit : 1;
    u16 useEntryPos : 1;
    u16 noSpark : 1;
    u16 struck : 1;
    u16 bit4 : 1;
    u16 shown : 1;
};

typedef struct {
    u8 pad_00[8];
    int scale;
} AttackOwner;

typedef struct {
    u32 flags;
    u8 pad_04[4];
    AttackOwner *owner;
} MotionHandle;

struct Actor {
    u8 pad_0000[0x234];
    u32 controlFlags;
    u8 pad_0238[0x760 - 0x238];
    int frame;
    u8 pad_0764[0x9b4 - 0x764];
    u8 player;
    u8 pad_09b5[0xfc8 - 0x9b5];
    MotionHandle motion;
    u8 pad_0fd4[0x10ec - 0xfd4];
    StateSetter setState;
    u8 pad_10f0[0x125c - 0x10f0];
    u32 hitFlags;
};

extern u16 func_ov052_020ceb9c(Actor *actor);
extern void func_ov021_020ac0d8(HitQuery *query);
extern VecFx32 *func_ov052_020ceb74(Actor *actor);
extern void func_ov021_020aa5d8(AttackShape *shape, VecFx32 *vec, fx32 *single, fx32 *balance, int rawScale);
extern void RotateOffsetAroundY(VecFx32 *out, const VecFx32 *origin, u16 angle, const VecFx32 *offset);
extern CollisionShape func_0203ad28(Sphere *storage, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void func_ov021_020ac118(HitResult *result);
extern void func_ov052_020d1880(HitResult *out, Actor *actor, AttackData *attack, SlotEntry *entry);
extern void func_ov021_020ac170(HitScan *scan);
extern BOOL func_ov021_020ac184(int player, HitQuery *query, HitResult *result, HitScan *scan);
extern BOOL func_ov021_020aa67c(MotionHandle *handle);
extern BOOL IsFacingWallContact(Actor *actor);
extern BOOL IsFacingNearbyTarget(Actor *actor, HitScan *scan);
extern void func_ov052_020cfda4(Actor *actor);
extern void func_ov052_020d14b4(Actor *actor, HitScan *scan, SlotEntry *entry, VecFx32 *target);

BOOL ScanAttackHits(Actor *actor, AttackData *attack, int arg, SlotEntry *entry)
{
    AttackOwner *owner = actor->motion.owner;
    BOOL result = FALSE;
    AttackShape *shape = &attack->shape;
    int angle;
    BOOL triggered;
    BOOL struck;
    int power;
    HitQuery query;
    HitScan scan;
    SweptShape swept;
    HitResult hit;
    Sphere sphere;
    VecFx32 offset;
    VecFx32 pos;
    fx32 radius;
    HitScan *cur;

    if (attack->startFrame > actor->frame || attack->endFrame <= actor->frame) {
        return FALSE;
    }
    angle = func_ov052_020ceb9c(actor);
    func_ov021_020ac0d8(&query);
    if (!entry->useEntryPos) {
        query.scale = shape->scale;
        query.arg = arg;
        query.angle = angle;
        if (actor->player == 0 && shape->useAnchor) {
            query.anchor = func_ov052_020ceb74(actor);
        }
        radius = shape->radius;
        offset = shape->offset;
        angle = (u16)(angle - 0x8000);
        func_ov021_020aa5d8(shape, &offset, &radius, &query.scale, owner->scale);
        RotateOffsetAroundY(&pos, func_ov052_020ceb74(actor), angle, &offset);
    } else {
        query.scale = 0x1000;
        query.arg = arg;
        query.angle = angle;
        func_ov021_020aa5d8(shape, &offset, &radius, &query.scale, owner->scale);
        pos = entry->pos;
    }
    swept.shape = func_0203ad28(&sphere, &pos, radius);
    swept.delta = query.delta;
    OffsetBoxByDelta(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
    query.shape = swept;
    func_ov021_020ac118(&hit);
    func_ov052_020d1880(&hit, actor, attack, entry);
    power = attack->power;
    hit.stun = attack->stun;
    triggered = FALSE;
    hit.bonus = 0;
    hit.power = power;
    hit.basePower = power;
    cur = &scan;
    func_ov021_020ac170(cur);
    while (func_ov021_020ac184(actor->player, &query, &hit, cur)) {
        struck = FALSE;
        switch (cur->kind) {
        case 2:
        case 4:
            struck = TRUE;
            if (!(cur->flags & 1)) {
                if (!(cur->flags & 0x20)) {
                    entry->hit = 1;
                }
            } else if (actor->player == 0) {
                triggered = TRUE;
            } else {
                cur->flags &= ~1;
                actor->hitFlags |= 0x4000;
            }
            if (cur->flags & 0x80) {
                entry->shown = 1;
            }
            break;
        case 3:
            if (!(cur->flags & 1)) {
                entry->hit = 1;
                entry->shown = 1;
                if (!hit.guarded) {
                    scan.combo = 0;
                }
                struck = TRUE;
            } else {
                if (entry->hit || !func_ov021_020aa67c(&actor->motion)) {
                    break;
                }
                triggered = IsFacingNearbyTarget(actor, cur);
                if (triggered) {
                    struck = TRUE;
                }
            }
            func_ov052_020cfda4(actor);
            break;
        case 1:
            if (cur->flags & 1) {
                if (entry->hit || !func_ov021_020aa67c(&actor->motion) || !(actor->controlFlags & 2) || cur->side != 1) {
                    break;
                }
                triggered = IsFacingWallContact(actor);
                if (triggered) {
                    struck = TRUE;
                }
            }
            if (entry->noSpark) {
                struck = TRUE;
            }
            break;
        }
        if (struck) {
            entry->struck = 1;
            if (!entry->noSpark) {
                func_ov052_020d14b4(actor, cur, entry, &pos);
            }
            if (entry->onHit != NULL) {
                entry->onHit(actor, cur, entry);
            }
            func_ov052_020cfda4(actor);
        }
        if (scan.state == 3 && entry->shown && !hit.guarded) {
            scan.state = 5;
        }
    }
    if (triggered) {
        if (actor->setState(actor, 0xe) == 0xe) {
            result = TRUE;
        }
        func_ov052_020cfda4(actor);
    }
    return result;
}
