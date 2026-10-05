#include "nitro/types.h"

typedef struct {
    u8 pad[0x2e6];
    u16 facing;
    u16 targetFacing;
} Actor;

extern s64 _ll_mul(s64 a, s64 b);
extern void func_ov001_02090f64(Actor *actor, int degrees);

void TurnActorFacingDegrees(Actor *actor, int degrees, int smooth) {
    if (smooth == 0) {
        func_ov001_02090f64(actor, degrees);
        return;
    }
    actor->targetFacing = (u16)((_ll_mul(degrees, 0xB60B60B60BLL) + 0x80000000000LL) >> 44);
}
