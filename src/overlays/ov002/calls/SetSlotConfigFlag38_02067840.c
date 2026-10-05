#include "nitro/types.h"

extern u32 func_ov002_02066fe0(void);

void SetSlotConfigFlag38_02067840(u32 value, s32 slotIndex) {
    u32 slot = func_ov002_02066fe0() + slotIndex * 0x4c;
    *(u32 *)(slot + 0x38) = (*(u32 *)(slot + 0x38) & 0xfff7ffff) | ((value & 1) << 0x13);
}
