#include "nitro/types.h"

typedef struct HandleTable {
    u32 unk_00;
    int count;
} HandleTable;

extern HandleTable data_020608c8;
extern u32 *data_02060940[];

void ClearHandleActiveFlags(void)
{
    int i;

    for (i = 0; i < data_020608c8.count; i++) {
        *data_02060940[i] &= ~0x80000000;
    }
}
