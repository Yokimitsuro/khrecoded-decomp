#include "nitro/types.h"

extern u32 data_ov021_020b560c;
extern u32 AttachActorToStageNode();
extern u32 ResolveStageActorRef();
extern u32 ResolveTaggedValueRef();

/* Leaf script command: stop actor motion. */
u32 ScriptCmd_StopActorMotion(u32 context)
{
    s32 actor;

    actor = ResolveTaggedValueRef();
    actor = ResolveStageActorRef(context, *(u32 *)(actor + 4));
    if (actor == 0) {
        return 0;
    }
    AttachActorToStageNode(actor, 0, &data_ov021_020b560c, 0);
    return 0;
}
