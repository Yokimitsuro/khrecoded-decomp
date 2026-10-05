#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x928];
    u64 flags;
    u8 player;
} HitActor;

extern void *func_ov001_0206db78(int player);
extern BOOL func_ov001_020645c8(u32 value);
extern BOOL func_ov059_020cc018(HitActor *actor, void *out);

BOOL Actor_BuildHitSphereWithCue(HitActor *actor, void *out)
{
    func_ov001_0206db78(actor->player);
    if (actor->flags & 0x40) {
        func_ov001_020645c8(0x3520);
    }
    return func_ov059_020cc018(actor, out);
}
