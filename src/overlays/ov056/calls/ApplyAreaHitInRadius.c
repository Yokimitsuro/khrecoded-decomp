#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef BOOL (*RecordFilter)(s32 recordId, void *userData);
typedef BOOL (*RecordVisitor)(s32 recordId, VecFx32 *position, void *userData);

typedef struct {
    s8 team;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x15];
    u8 unk_25;
    u8 pad_26[6];
} HitParams;

typedef struct {
    u8 pad_00[0x3C];
    s8 team;
} HitOwner;

typedef struct {
    HitParams params;
    HitOwner *owner;
    void *extra;
} AreaHitSearch;

extern void ResetAnimationTrackState(HitParams *params);
extern BOOL func_ov056_020d51ac(s32 recordId, void *userData);
extern BOOL func_ov056_020d520c(s32 recordId, VecFx32 *position, void *userData);
extern void ForEachRecordInRadius(RecordFilter filter, RecordVisitor visitor, VecFx32 *center, fx32 radius, void *userData);

void ApplyAreaHitInRadius(VecFx32 *center, fx32 radius, HitOwner *owner, void *extra)
{
    AreaHitSearch search;

    ResetAnimationTrackState(&search.params);
    search.params.team = owner->team;
    search.params.unk_25 = 0;
    search.owner = owner;
    search.extra = extra;
    ForEachRecordInRadius(func_ov056_020d51ac, func_ov056_020d520c, center, radius, &search);
}
