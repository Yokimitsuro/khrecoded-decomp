#include "src/calls/scene_control.h"

extern void MI_CpuFill8(void *dest, u32 value, u32 size);

s32 ResetSceneCtl(void)
{
    MI_CpuFill8(&gSceneController, 0, sizeof(gSceneController));
    return 1;
}
