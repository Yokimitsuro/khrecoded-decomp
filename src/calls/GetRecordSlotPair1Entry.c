#include "nitro/types.h"

typedef struct {
    u8 data[0x30];
} SlotPair1Entry;

typedef struct {
    u8 pad_00[0x10];
    SlotPair1Entry *slotPair1;
} RecordManager;

extern RecordManager *data_020613d0;

/* Gets a slot-pair-1 table entry pointer. */
SlotPair1Entry *GetRecordSlotPair1Entry(s32 index)
{
    RecordManager *manager = data_020613d0;

    if (index == -1) {
        return 0;
    }
    if (manager == 0 || manager->slotPair1 == 0) {
        return 0;
    }
    return manager->slotPair1 + index;
}
