#include "nitro/types.h"

extern void func_ov001_020874f4(void *request, u32 kind, u32 dropIndex, u32 fixedItem, u32 variant,
                                u32 saveGroup, u32 saveIndex);

void DropRequest_InitKind0(void *request, u32 dropIndex, u32 variant, u32 saveGroup, u32 saveIndex)
{
    func_ov001_020874f4(request, 0, dropIndex, 0xffffffff, variant, saveGroup, saveIndex);
}
