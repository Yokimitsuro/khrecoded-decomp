#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    void *data;
    s32 bounds[6];
    s32 kind;
    u8 pad_20[0x24];
    s16 *hitIds;
} HitRecord;

typedef struct {
    fx32 distance;
    VecFx32 direction;
    s32 pad_10[2];
} HitResult;

typedef struct {
    u16 id;
    u16 isPartner : 1;
    u16 isLocked : 1;
    u16 flagBits : 14;
    u16 kind;
    u16 pad_06;
    VecFx32 position;
    s32 extent[4];
} EventTargetInfo;

typedef struct {
    s32 id;
    s32 count;
    s32 param;
    VecFx32 start;
    VecFx32 end;
    u32 result;
} PathSegment;

typedef struct {
    u8 pad_00[0x10];
    u8 passive;
    u8 pad_11[0x13];
    u16 isActive : 1;
    u16 isReactive : 1;
} HitTarget;

typedef struct HitManager {
    u8 pad_00[0xbc];
    VecFx32 origin;
    u8 pad_c8[0x114];
    s32 state;
    u8 pad_1e0[0x4c];
    s32 (*getState)(struct HitManager *manager);

} HitManager;

typedef struct {
    u32 flags;
    u32 pad_04;
    s32 kind;
    VecFx32 point;
    u16 targetId;
    u16 partId;
} HitReport;

extern HitManager *GetBoundedEntryField(int index);
extern s32 func_ov001_020878c4(HitRecord *record, HitResult *result, u16 *partId);
extern BOOL func_ov021_020abfd0(HitRecord *record, HitResult *result);
extern BOOL func_ov001_02087988(u32 id, EventTargetInfo *out);
extern u32 func_0202a9e4(u32 range);
extern VecFx32 ComputeKnockbackVector(HitRecord *record, HitTarget *target, VecFx32 *position);
extern void InitPathSegment(PathSegment *segment, s32 id, s32 count, s32 param, const VecFx32 *start, const VecFx32 *end);
extern BOOL func_ov021_020ac35c(HitTarget *target, PathSegment *segment);
extern void AddSessionCounter(int index, int amount);
extern BOOL IsObjectIdle(HitTarget *target);
extern VecFx32 GetShapeCenter(const HitRecord *shape);
extern void func_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

BOOL ResolveHitContacts(int owner, HitRecord *record, HitTarget *target, HitReport *report)
{
    HitManager *manager = GetBoundedEntryField(owner);
    BOOL done = FALSE;
    s32 id;
    HitResult result;
    VecFx32 offset;
    VecFx32 centerCopy;
    EventTargetInfo info;
    PathSegment segment;
    VecFx32 end;
    VecFx32 contact;
    VecFx32 center;
    u16 partId;

    do {
        BOOL hit = FALSE;
        int i;
        BOOL seen;
        s16 *ids;

        id = func_ov001_020878c4(record, &result, &partId);
        if (id == 0) {
            break;
        }
        ids = record->hitIds;
        if (ids != NULL) {
            seen = FALSE;

            for (i = 0; i < 8; i++) {
                if (id == ids[i]) {
                    seen = TRUE;
                    break;
                }
            }
            if (seen) {
                continue;
            }
        }
        if (!func_ov021_020abfd0(record, &result)) {
            continue;
        }
        if (!func_ov001_02087988(id, &info)) {
            continue;
        }
        if (target != NULL && target->passive == 0) {
            s32 state;

            if (manager->getState != NULL) {
                state = manager->getState(manager);
            } else {
                state = manager->state;
            }
            if (state == 7 && !info.isLocked && func_0202a9e4(100) < 75) {
                report->flags |= 0x20;
                hit = TRUE;
            }
        }
        if (info.isLocked && target != NULL && target->isReactive && !target->isActive) {
            ids = record->hitIds;
            if (ids != NULL) {
                for (i = 0; i < 8; i++) {
                    if (ids[i] == -1) {
                        ids[i] = id;
                        break;
                    }
                }
            }
            continue;
        }
        if (target != NULL && !hit) {

            contact = ComputeKnockbackVector(record, target, &info.position);
            end = contact;
            InitPathSegment(&segment, id, partId, owner, &manager->origin, &end);
            if (func_ov021_020ac35c(target, &segment)) {
                report->flags |= 4;
                AddSessionCounter(8, 1);
            }
            if (segment.result != 0x80000000) {
                done = TRUE;
                if (segment.result & 1) {
                    if (IsObjectIdle(target)) {
                        report->flags |= 1;
                    } else {
                        report->flags |= 0x10;
                    }
                } else if (target->isActive) {
                    report->flags |= 2;
                }
                if (info.isLocked) {
                    report->flags |= 0x80;
                }
            }
        } else {
            done = TRUE;
        }
        if (done) {

            ids = record->hitIds;
            if (ids != NULL) {
                for (i = 0; i < 8; i++) {
                    if (ids[i] == -1) {
                        ids[i] = id;
                        break;
                    }
                }
            }
            report->kind = 4;
            report->targetId = id;
            report->partId = partId;
            center = GetShapeCenter(record);
            centerCopy = center;
            switch (record->kind) {
            case 3:
            case 4:
                report->point = info.position;
                break;
            default:
                func_01ffafb4(result.distance, &result.direction, &offset);
                VEC_Add(&centerCopy, &offset, &report->point);
                break;
            }
        }
    } while (id != 0 && done != TRUE);
    return id == 0;
}
