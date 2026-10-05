#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PathSegment {
    s32 id;
    s32 count;
    s32 param;
    VecFx32 start;
    VecFx32 end;
    s32 result;
} PathSegment;

typedef struct ScaledStats {
    u8 pad_00[0x12];
    u8 element;
    u8 pad_13[0x28 - 0x13];
} ScaledStats;

typedef struct StatSource {
    u8 pad_000[0x3c];
    s8 entryIndex;
    u8 pad_03d[0xe8 - 0x3d];
    VecFx32 origin;
    u8 pad_0f4[0x188 - 0xf4];
    s16 owner;
    u8 pad_18a[0x198 - 0x18a];
    s16 groupId;
    u8 pad_19a[0x1a0 - 0x19a];
    int percent;
    int flags;
    fx32 scale;
    int kind;
} StatSource;

typedef struct HitRequest {
    u8 pad_00[4];
    VecFx32 position;
    u8 pad_10[0x2c - 0x10];
    StatSource *source;
} HitRequest;

extern void *func_ov001_0206db5c(int index);
extern void func_ov021_020ac118(void *obj);
extern void func_ov056_020d4260(StatSource *source, ScaledStats *stats, s32 percent, u8 flags, fx32 scale);
extern void func_ov021_020ac124(PathSegment *segment, s32 id, s32 count, s32 param, const VecFx32 *start, const VecFx32 *end);
extern void func_ov021_020ac35c(ScaledStats *stats, PathSegment *segment);
extern int func_ov021_020a8cc0(HitRequest *request, int groupId);
extern u32 SpawnSoundSlot(u32 owner, u32 kind, VecFx32 *position, u32 flags);

int ApplyScaledPathHit(s32 attacker, VecFx32 *position, HitRequest *request)
{
    StatSource *source = request->source;
    ScaledStats stats;
    PathSegment segment;

    func_ov001_0206db5c(source->entryIndex);
    func_ov021_020ac118(&stats);
    func_ov056_020d4260(source, &stats, (u8)source->percent, (u8)source->flags, source->scale);
    switch (source->kind) {
    case 7:
    default:
        stats.element = 6;
        break;
    case 6:
        stats.element = 7;
        break;
    case 8:
        stats.element = 5;
        break;
    }
    func_ov021_020ac124(&segment, attacker, -1, source->entryIndex, &source->origin, NULL);
    func_ov021_020ac35c(&stats, &segment);
    if (segment.result != (s32)0x80000000) {
        request->position = *position;
        func_ov021_020a8cc0(request, request->source->groupId);
        SpawnSoundSlot(source->owner, 1, position, 0);
    }
    return 0;
}
