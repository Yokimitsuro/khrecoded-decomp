#include "nitro/types.h"

extern u32 func_ov001_02096a08();
extern u32 func_ov021_020b0270();
extern u32 ResolveTaggedValueRef();

/* Leaf script command: enables actor group flag. */
u32 ScriptCmd_SetActorGroupFlag(u32 context)
{
    s32 actor;

    actor = ResolveTaggedValueRef();
    actor = func_ov021_020b0270(context, *(u32 *)(actor + 4));
    if (actor != 0) {
        func_ov001_02096a08(actor, 1);
    }
    return 0;
}
