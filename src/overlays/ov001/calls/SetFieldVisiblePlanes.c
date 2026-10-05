#include "nitro/types.h"
#include "nitro/hw.h"

extern u32 func_ov001_0207b3f4(void);

static inline void SetMainVisiblePlane(u32 planeMask)
{
    *(vu32 *)REG_DISPCNT_ADDR = (*(vu32 *)REG_DISPCNT_ADDR & ~0x1f00) | (planeMask << 8);
}

static inline void SetSubVisiblePlane(u32 planeMask)
{
    *(vu32 *)REG_DB_DISPCNT_ADDR = (*(vu32 *)REG_DB_DISPCNT_ADDR & ~0x1f00) | (planeMask << 8);
}

void SetFieldVisiblePlanes(void)
{
    SetMainVisiblePlane(0xf);
    if (func_ov001_0207b3f4() == 0) {
        SetSubVisiblePlane(0x1e);
    } else {
        SetSubVisiblePlane(0x1f);
    }
}
