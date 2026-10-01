#include "libs/nitro/os/os_types_internal.h"

#define REG16(address) (*(volatile u16 *)(address))
#define REG32(address) (*(volatile u32 *)(address))

#define reg_GX_DISP3DCNT      REG16(0x04000060)
#define reg_G3_POLYGON_ATTR   REG32(0x040004a4)
#define reg_G3_TEXIMAGE_PARAM REG32(0x040004a8)
#define reg_G3_TEXPLTT_BASE   REG32(0x040004ac)
#define reg_G3X_GXSTAT        REG32(0x04000600)

extern void G3X_ResetMtxStack(void);

void G3X_Reset(void)
{
    while (reg_G3X_GXSTAT & 0x08000000) {
    }

    reg_G3X_GXSTAT |= 0x00008000;
    reg_GX_DISP3DCNT |= 0x2000;
    reg_GX_DISP3DCNT |= 0x1000;
    G3X_ResetMtxStack();

    reg_G3_POLYGON_ATTR = 0x001f0080;
    reg_G3_TEXIMAGE_PARAM = 0;
    reg_G3_TEXPLTT_BASE = 0;
}
