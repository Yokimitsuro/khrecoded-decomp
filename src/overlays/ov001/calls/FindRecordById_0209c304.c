#include "nitro/types.h"

extern u32 func_ov001_0209c068();

u32 FindRecordById_0209c304(int id)
{
    u32 record;

    if (id == 0) {
        return 0;
    }
    record = func_ov001_0209c068((int)(short)id);
    return record;
}
