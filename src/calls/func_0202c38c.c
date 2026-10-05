#include "nitro/types.h"

extern u32 RequestFileLoad(u32 fileId, int alignFlag, u32 param3, u32 param4);

u32 func_0202c38c(u32 fileId, u32 param2, u32 param3, u32 param4)
{
    return RequestFileLoad(fileId, 1, param2, param4);
}
