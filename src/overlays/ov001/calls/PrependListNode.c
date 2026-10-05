#include "nitro/types.h"

extern u32 data_ov001_020a04f8;
extern void *func_ov001_0207f060();
extern void FieldObject_Activate(void *node, u32 param3);

void PrependListNode(u32 param1, u32 param2, u32 param3)
{
    u8 *node;

    node = func_ov001_0207f060();
    *(u16 *)(node + 0x4e) = *(u16 *)(node + 0x4e) | 2;
    *(u8 **)(node + 4) = *(u8 **)(data_ov001_020a04f8 + 8);
    *(u8 **)node = 0;
    if (*(u8 **)(data_ov001_020a04f8 + 8) != 0) {
        *(u8 **)*(u8 **)(data_ov001_020a04f8 + 8) = node;
    }
    *(u8 **)(data_ov001_020a04f8 + 8) = node;
    FieldObject_Activate(node, param3);
}
