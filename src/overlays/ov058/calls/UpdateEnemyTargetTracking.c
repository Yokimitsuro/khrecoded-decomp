#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    u8 data[0x28];
} SegmentStorage;

typedef struct {
    u8 pad_000[0x194];
    u8 dead;
} HitOwner;

typedef struct {
    u8 pad_00[0x14];
    HitOwner *owner;
} HitObject;

typedef struct {
    HitObject *object;
    int kind;
    int pad_08;
} ContactHit;

typedef struct {
    ContactHit hits[16];
    VecFx32 normals[16];
    u8 count;
    u8 pad_181[0x20];
    u8 locked;
    u8 pad_1a2[2];
} QueryWorkspace;

typedef struct {
    u32 words[0x18];
} CollisionQuery;

typedef struct {
    u8 pad_00[0x10];
    HitObject *object;
} CollisionHit;

typedef struct {
    u8 kind;
    u8 pad_01[3];
    int entry;
    VecFx32 position;
} TargetInfo;

typedef struct {
    s32 mode;
    u32 flags;
    u8 pad_08[4];
    s32 targetKind;
    u8 pad_10[8];
    s32 cooldown;
    u8 pad_1c[0x0c];
    s16 heading;
} AiState;

typedef struct {
    u8 pad_00[0xc];
    u16 flags;
} AttackResult;

typedef struct Enemy Enemy;
typedef VecFx32 *(*OriginGetter)(Enemy *enemy);

struct Enemy {
    u8 pad_000[0xbc];
    VecFx32 origin;
    u8 pad_0c8[0x224 - 0xc8];
    OriginGetter getOrigin;
    u8 pad_228[0x230 - 0x228];
    void *model;
    u8 pad_234[0x344 - 0x234];
    QueryWorkspace contacts;
    u8 pad_4e8[0x9b4 - 0x4e8];
    u8 team;
    u8 pad_9b5[0x9c0 - 0x9b5];
    s32 state;
    u8 pad_9c4[0x1048 - 0x9c4];
    TargetInfo target;
    u8 pad_105c[0x1258 - 0x105c];
    AiState ai;
};

extern Enemy *data_ov058_020d8a40;

extern void func_ov058_020d546c(Enemy *enemy);
extern VecFx32 *func_ov052_020ceb74(Enemy *enemy);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern BOOL func_ov001_0206c3a4(TargetInfo *target);
extern BOOL ReadActiveMenuState(TargetInfo *out);
extern BOOL func_ov001_0206c348(TargetInfo *target, u8 team, u32 kinds);
extern VecFx32 *func_ov001_0206c3f4(TargetInfo *target);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollisionShape func_0203ade0(SegmentStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern CollisionHit *SweepWorldCollision(CollisionQuery *query);

void UpdateEnemyTargetTracking(Enemy *enemy, AttackResult *result)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    CollisionQuery query;
    TargetInfo info;
    SegmentStorage segment;
    CollisionShape segmentShape;
    VecFx32 start;
    VecFx32 end;
    VecFx32 toTarget;
    VecFx32 toPlayer;
    CollisionShape segmentResult;
    VecFx32 diff;
    VecFx32 axis;
    TargetInfo *target = &enemy->target;
    AiState *ai = &enemy->ai;
    VecFx32 *targetPos;
    VecFx32 *origin;
    CollisionHit *hit;
    BOOL found;
    int state;
    BOOL busy;
    u32 kinds;
    fx32 cross;

    if (ai->mode == 5) {
        ai->mode = 1;
    }
    state = enemy->state;
    found = FALSE;
    if (ai->targetKind != 5 && ai->targetKind != 6) {
        func_ov058_020d546c(enemy);
        return;
    }
    if (ai->flags & 0x80000) {
        func_ov058_020d546c(enemy);
        return;
    }
    if (enemy->contacts.locked) {
        func_ov058_020d546c(enemy);
        return;
    }
    if (ai->cooldown > 0) {
        func_ov058_020d546c(enemy);
        return;
    }
    if (VEC_Distance(func_ov052_020ceb74(data_ov058_020d8a40), func_ov052_020ceb74(enemy)) > 0xf000) {
        func_ov058_020d546c(enemy);
        ai->cooldown = 0x3c000;
        return;
    }
    busy = TRUE;
    switch (state) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
    case 11:
        busy = FALSE;
        break;
    }
    if (busy) {
        return;
    }
    if (!func_ov001_0206c3a4(target)) {
        if (ReadActiveMenuState(&info)) {
            if ((info.kind == 1 && ai->targetKind == 5) || (info.kind == 3 && ai->targetKind == 6)) {
                *target = info;
                found = TRUE;
            }
        }
    } else if ((target->kind == 1 && ai->targetKind == 5) || (target->kind == 3 && ai->targetKind == 6)) {
        found = TRUE;
    }
    if (!found) {
        kinds = 1;
        if (ai->targetKind == 5) {
            kinds = 2;
        }
        if (!func_ov001_0206c348(&enemy->target, enemy->team, kinds)) {
            func_ov058_020d546c(enemy);
            return;
        }
    }
    targetPos = func_ov001_0206c3f4(target);
    origin = enemy->getOrigin != NULL ? enemy->getOrigin(enemy) : &enemy->origin;
    start = *origin;
    end = *targetPos;
    func_01ff9e3c(&end, &start, &diff);
    axis = diff;
    segmentResult = func_0203ade0(&segment, &start, &end, &axis, func_01ffaff4(&axis, &axis));
    segmentShape = segmentResult;
    CollisionQuery_Init(&query, 0, enemy->model, 0xe, 1, 0, &segmentShape, &workspace, NULL);
    sweep = query;
    hit = SweepWorldCollision(&sweep);
    if (hit != NULL && hit->object != NULL && hit->object->owner->dead == 0) {
        if (VEC_Distance(&segmentShape.data[1], origin) < 0x16cd) {
            result->flags |= 2;
        } else {
            func_01ff9e3c(targetPos, origin, &toTarget);
            func_01ff9e3c(func_ov052_020ceb74(data_ov058_020d8a40), origin, &toPlayer);
            toPlayer.y = 0;
            toTarget.y = 0;
            cross = (fx32)(((s64)toTarget.x * toPlayer.z + 0x800) >> 12) - (fx32)(((s64)toTarget.z * toPlayer.x + 0x800) >> 12);
            if (cross >= 0) {
                ai->heading = (u16)ai->heading + 0x3fff;
            } else {
                ai->heading = (u16)ai->heading - 0x3fff;
            }
        }
    }
    {
        int i;
        QueryWorkspace *contacts = &enemy->contacts;
        for (i = 0; i < contacts->count; i++) {
            ContactHit *contact = &contacts->hits[i];
            if (contact->kind == 4 && contact->object->owner->dead == 0) {
                result->flags |= 2;
                break;
            }
        }
    }
    ai->mode = 5;
}
