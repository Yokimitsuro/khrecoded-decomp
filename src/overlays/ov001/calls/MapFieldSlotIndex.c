#include "nitro/types.h"

typedef struct SlotMap {
    int slots[3];
} SlotMap;

extern const SlotMap data_ov001_0209dbc8;
extern int CountAssignedFieldSlots(void);

int MapFieldSlotIndex(int index)
{
    SlotMap map = data_ov001_0209dbc8;

    if (CountAssignedFieldSlots() > 0) {
        index = map.slots[index];
    }
    return index;
}
