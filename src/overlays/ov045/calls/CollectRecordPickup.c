#include "nitro/types.h"

typedef struct {
    int id;
    u8 pad04[0x3c];
    int value;
} SlotEntry;

typedef struct {
    u8 pad00[0x19f0];
    s16 count;
    u16 pad19f2;
    int values[1];
} PickupList;

extern u16 GetByteCounterOrDefault(int index);
extern SlotEntry *GetRecordSlotPair0Entry(s32 index);
extern void func_02029254(int id, int count);
extern void SetGlobalPackedBit(int bitIndex);
extern void func_ov001_020645dc(int soundId);

void CollectRecordPickup(PickupList *list, int id)
{
    BOOL grant = TRUE;
    BOOL inGroup;

    if (id >= 0xd0 && id <= 0x10f) {
        inGroup = TRUE;
    } else {
        inGroup = FALSE;
    }
    if (inGroup) {
        int i;
        int base = (id - 0xd0) / 5 * 5 + 0xd0;

        for (i = 0; i < 5; i++) {
            if (GetByteCounterOrDefault(base + i) != 0) {
                grant = FALSE;
                break;
            }
        }
    }
    if (grant) {
        SlotEntry *entry = GetRecordSlotPair0Entry(id);

        list->values[list->count++] = entry->value;
        if (!inGroup) {
            func_02029254(entry->id, 0);
            SetGlobalPackedBit(entry->id);
        } else {
            func_ov001_020645dc(0x371e);
        }
    }
}

