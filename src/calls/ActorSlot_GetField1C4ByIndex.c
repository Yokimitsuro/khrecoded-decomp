#include "src/calls/actor_registry.h"

s16 ActorSlot_GetField1C4ByIndex(int index)
{
    ActorSlotTail *tail = (ActorSlotTail *)((u8 *)gActorRegistry->slots[index] + 0x100);
    return tail->field_1c4;
}
