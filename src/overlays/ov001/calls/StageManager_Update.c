#include "nitro/types.h"

extern int data_ov001_0209f2e8;
extern void func_ov001_0209b978(u32 updateParam);

void StageManager_Update(u32 updateParam)
{
    if (data_ov001_0209f2e8 != -1) {
        func_ov001_0209b978(updateParam);
    }
}
