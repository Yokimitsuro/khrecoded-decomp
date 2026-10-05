#include "nitro/types.h"

extern u32 FileLoader_LoadAlloc(u32 fileId, int alignFlag, u32 param3, u32 param4);

u32 func_0202c4a0(u32 fileId, u32 param2, u32 param3, u32 param4)
{
    return FileLoader_LoadAlloc(fileId, 1, param2, param4);
}
