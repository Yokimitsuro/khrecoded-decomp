#include "nitro/types.h"

extern void ZeroActorTailBlock(void *block);
extern BOOL ReleaseActorResources(void *actor);

BOOL HandleActorLifecycleEvent(int event, void *actor)
{
    switch (event) {
    case 0:
        ZeroActorTailBlock(actor);
        break;
    case 1:
        ReleaseActorResources(actor);
        break;
    }
    return TRUE;
}
