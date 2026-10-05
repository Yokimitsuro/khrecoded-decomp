#include "nitro/types.h"

typedef struct SceneCtl {
    void *obj;
    void *entry;
    s32   curId;
    s32   pendId;
    s32   pendArg;
} SceneCtl;

extern SceneCtl data_0205fdec;
extern void MI_CpuFill8(void *dest, u32 value, u32 size);

s32 ResetSceneCtl(void)
{
    MI_CpuFill8(&data_0205fdec, 0, 0x14);
    return 1;
}
