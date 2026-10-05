#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} HandlerSlot;

typedef struct {
    u8 pad_000[0x9f8];
    HandlerSlot slots[3];
} PanelScene;

extern void CallVirtualHandlerSlot1(void *context, int arg);

void InvokeSlotHandlers(PanelScene *scene)
{
    int slotIndex;

    for (slotIndex = 0; slotIndex < 3; slotIndex++) {
        CallVirtualHandlerSlot1(&scene->slots[slotIndex], 0);
    }
}
