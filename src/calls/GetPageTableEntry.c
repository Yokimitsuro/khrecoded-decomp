#include "nitro/types.h"

extern u8 data_02055b10[];

u8 *GetPageTableEntry(u32 index)
{
    if (index > 5) {
        return NULL;
    }
    return data_02055b10 + index * 0x1a;
}
