#include "nitro/types.h"

extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern u32 ConfigureImageEntryList(int manager, u32 *config);

void InitObjManagerVariant(int manager, u32 *config)
{
    MI_CpuFill8((void *)manager, 0, 0x6434);
    *(u32 *)(manager + 0x6020) = 1;
    ConfigureImageEntryList(manager, config);
}
