#include "nitro/types.h"

extern u8 *GetStageController(u16 index);
extern u16 GetLargeRecordIndex(u8 *actor);

void RegisterActorSlotInEntity(u8 *actor)
{
    u8 *entity = GetStageController(*(u16 *)(actor + 0x1d2));

    if (entity != 0) {
        *(u16 *)(entity + 0xc) = GetLargeRecordIndex(actor);
    }
}
