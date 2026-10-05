#include "src/calls/actor_registry.h"

ActorSlotTail *ActorSlot_SetField1C4ByIndex(int index, u16 value)
{
    ActorSlotTail *tail = (ActorSlotTail *)((u8 *)gActorRegistry->slots[index] + 0x100);
    tail->field_1c4 = value;
    return tail;
}
