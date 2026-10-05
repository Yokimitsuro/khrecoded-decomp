#include "nitro/types.h"
#include "nnsys/gfd.h"

typedef struct {
    u32 loAddr;
    u32 hiAddr;
} PlttVramState;

typedef struct {
    u8 pad_00[0x92c];
    NNSGfdFrmTexVramState texStates[16];
    PlttVramState plttStates[16];
    u8 vramStateDepth;
} ActorRegistry;

extern void NNS_GfdGetFrmTexVramState(NNSGfdFrmTexVramState *state);
extern void NNS_GfdGetFrmPlttVramState(PlttVramState *state);
extern void OS_Terminate(void);
extern ActorRegistry *gActorRegistry;

u8 PushVramState(void)
{
    ActorRegistry *registry = gActorRegistry;

    if (registry->vramStateDepth < 16) {
        NNS_GfdGetFrmTexVramState(&registry->texStates[registry->vramStateDepth]);
        NNS_GfdGetFrmPlttVramState(&registry->plttStates[registry->vramStateDepth]);
        registry->vramStateDepth++;
    } else {
        OS_Terminate();
    }
    return registry->vramStateDepth;
}
