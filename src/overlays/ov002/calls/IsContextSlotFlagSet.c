#include "nitro/types.h"

typedef struct ContextSlot {
    u8 pad_00[0x38];
    u32 unk_38_b0 : 17;
    u32 configFlag : 1;
    u32 unk_38_b18 : 14;
    u8 pad_3C[0x10];
} ContextSlot;

extern ContextSlot *func_ov002_02066fe0(void);

u32 IsContextSlotFlagSet(int index)
{
    return func_ov002_02066fe0()[index].configFlag;
}
