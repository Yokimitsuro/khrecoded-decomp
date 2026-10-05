#include "nitro/types.h"

extern u8 *GetStageEventRecord(u16 index);
extern u16 GetLargeRecordIndex(u8 *actor);

void RegisterActorSlotInRecord(u8 *actor)
{
    u8 *record = GetStageEventRecord(*(u16 *)(actor + 0x1d2));

    if (record != 0) {
        *(u16 *)(record + 0x10) = GetLargeRecordIndex(actor);
    }
}
