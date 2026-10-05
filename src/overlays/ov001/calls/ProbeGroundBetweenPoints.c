#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct HitOwner {
    u8 pad_00[0x6c];
    s32 kind;
} HitOwner;

typedef struct HitResult {
    u8 pad_00[0x10];
    HitOwner *owner;
} HitResult;

typedef struct GroundProbe {
    u8 pad_000[0x26c];
    u32 stateBits : 31;
    u32 stateTop : 1;
    u8 pad_270[0x18];
    u16 flagBits : 15;
    u16 probeDisabled : 1;
    u8 pad_28a[6];
    fx32 groundHeight;
    u8 pad_294[0x2c];
    u8 probeArea[4];
    fx32 baseHeight;
    u8 pad_2c8[0x64];
    fx32 minReach;
} GroundProbe;

extern int func_ov001_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern HitResult *ProbeGroundBelowActor(GroundProbe *probe, void *area, VecFx32 *from, VecFx32 *to, fx32 reach);

static inline s32 GetSessionMode(void)
{
    if (func_ov001_02063a24()) {
        return func_ov001_02063a38();
    }
    return 0;
}

HitResult *ProbeGroundBetweenPoints(GroundProbe *probe, VecFx32 *from, VecFx32 *to)
{
    fx32 reach;
    HitResult *hit;

    if (GetSessionMode() == 7) {
        return NULL;
    }
    reach = from->y - probe->baseHeight;
    if (reach >= 0) {
        reach = probe->minReach;
    }
    if (reach < 0) {
        reach = -reach;
    }
    if (reach < probe->minReach) {
        reach = probe->minReach;
    }
    hit = ProbeGroundBelowActor(probe, probe->probeArea, from, to, reach);
    if (hit != NULL) {
        if (hit->owner != NULL && hit->owner->kind == 5) {
            probe->groundHeight = -0x3000;
            return NULL;
        }
        probe->groundHeight = to->y;
    } else if (!probe->probeDisabled) {
        if (GetSessionMode() != 4) {
            probe->groundHeight = -0x3000;
        } else if (!(probe->stateBits & 8)) {
            probe->groundHeight = -0x3000;
        }
    }
    return hit;
}
