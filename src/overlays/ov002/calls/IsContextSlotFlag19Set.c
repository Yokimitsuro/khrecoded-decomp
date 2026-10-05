#include "nitro/types.h"

typedef struct ContextSlot {
    u8 pad_00[0x38];
    u32 unk_38_b0 : 19;
    u32 activeFlag : 1;
    u32 unk_38_b20 : 12;
    u8 pad_3C[0x10];
} ContextSlot;

extern ContextSlot *func_ov002_02066fe0(void);

BOOL IsContextSlotFlag19Set(int index)
{
    return func_ov002_02066fe0()[index].activeFlag ? TRUE : FALSE;
}
