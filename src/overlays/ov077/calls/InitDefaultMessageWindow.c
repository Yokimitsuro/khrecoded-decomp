#include "nitro/types.h"

extern void func_ov077_020c83fc(void *window, u32 owner, s16 x, s16 y, u16 width, u16 height,
                                       int animParam, u32 onClose, u32 closeParam);

void InitDefaultMessageWindow(void *window, u32 owner, s16 x, s16 y, u16 width, u16 height, u32 onClose)
{
    func_ov077_020c83fc(window, owner, x, y, width, height, 0x96, onClose, 0x412);
}
