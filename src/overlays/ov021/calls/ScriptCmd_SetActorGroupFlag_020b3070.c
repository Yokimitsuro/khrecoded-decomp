#include "nitro/types.h"

extern u32 NotifyActorGroupMembers();
extern u32 ResolveEventRecordRef();
extern u32 ResolveTaggedValueRef();

/* Leaf script command: disables actor group flag. */
u32 ScriptCmd_SetActorGroupFlag_020b3070(u32 context)
{
    s32 actor;

    actor = ResolveTaggedValueRef();
    actor = ResolveEventRecordRef(context, *(u32 *)(actor + 4));
    if (actor != 0) {
        NotifyActorGroupMembers(actor, 0);
    }
    return 0;
}
