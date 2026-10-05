#include "nitro/types.h"

typedef struct {
    u8 data[0x48];
} SlotPair0Entry;

typedef struct {
    u8 pad_00[8];
    SlotPair0Entry *slotPair0;
} RecordManager;

extern RecordManager *gRecordManager;

/* Gets a slot-pair-0 table entry pointer. */
SlotPair0Entry *GetRecordSlotPair0Entry(s32 index)
{
    RecordManager *manager = gRecordManager;

    if (index == -1) {
        return 0;
    }
    if (manager == 0 || manager->slotPair0 == 0) {
        return 0;
    }
    return manager->slotPair0 + index;
}
