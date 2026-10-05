#include "nitro/types.h"

extern void ClearAllActorSlots(void);

u32 ScriptOp_RunActorPass(u8 *scriptContext)
{
    if (*(u32 *)(*(u8 **)(scriptContext + 0x1c8) + 0x4c) != 0) {
        ClearAllActorSlots();
    }
    return 1;
}
