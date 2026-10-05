#include "nitro/types.h"
#include "nnsys/gfd.h"

typedef struct {
    u32 loAddr;
    u32 hiAddr;
} PlttVramState;

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0a;
    u8 vramDepth;
} ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[0x200];
    u8 pad_820[0x10c];
    NNSGfdFrmTexVramState texStates[16];
    PlttVramState plttStates[16];
    u8 vramStateDepth;
} ActorRegistry;

extern void NNS_GfdSetFrmTexVramState(const NNSGfdFrmTexVramState *state);
extern void NNS_GfdSetFrmPlttVramState(const PlttVramState *state);
extern void Obj_ConditionalShutdown(ActorSlot *slot, u16 index);
extern void OS_Terminate(void);
extern ActorRegistry *data_0206083c;

void PopVramState(void)
{
    ActorRegistry *registry = data_0206083c;
    int i;

    if (registry->vramStateDepth == 0) {
        OS_Terminate();
    }
    for (i = 0; i < 0x200; i++) {
        ActorSlot *slot = registry->slots[i];
        if (slot != NULL && slot->vramDepth >= registry->vramStateDepth && (slot->flags & 0x800) == 0) {
            Obj_ConditionalShutdown(slot, i);
        }
    }
    registry->vramStateDepth--;
    NNS_GfdSetFrmTexVramState(&registry->texStates[registry->vramStateDepth]);
    NNS_GfdSetFrmPlttVramState(&registry->plttStates[registry->vramStateDepth]);
}
