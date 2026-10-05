#include "nitro/types.h"

int FindFreeRecordSlot(u8 *recordArray)
{
    int recordIndex = 0;

    do {
        s32 *recordFlags = (s32 *)(recordArray + recordIndex * 0x8c + 0x7c);
        if (((u32)(*recordFlags << 0x1f) >> 0x1f) == 0) {
            return recordIndex;
        }
        recordIndex = recordIndex + 1;
    } while (recordIndex < 0x80);

    return -1;
}
