#include "nitro/types.h"

extern u32 data_ov001_020a04f8;
extern void func_ov001_0207f670(void *node);

void DestroyListNodes(void)
{
    u8 *node;

    for (node = *(u8 **)(data_ov001_020a04f8 + 8); node != 0; node = *(u8 **)(node + 4)) {
        func_ov001_0207f670(node);
    }
    *(u32 *)(data_ov001_020a04f8 + 8) = 0;
}
