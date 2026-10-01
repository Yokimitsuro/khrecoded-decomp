#include "libs/nitro/os/os_types_internal.h"

#define REG16(address) (*(volatile u16 *)(address))
#define REG32(address) (*(volatile u32 *)(address))

#define reg_GX_DISP3DCNT       REG16(0x04000060)
#define reg_G2_BG0CNT          REG16(0x04000008)
#define reg_G2_BG0OFS          REG32(0x04000010)
#define reg_G3X_CLEAR_COLOR    REG32(0x04000350)
#define reg_G3X_CLEAR_DEPTH    REG16(0x04000354)
#define reg_G3X_CLRIMAGE_OFFSET REG16(0x04000356)
#define reg_G3X_FOG_COLOR      REG32(0x04000358)
#define reg_G3X_FOG_OFFSET     REG16(0x0400035c)
#define reg_G3_END_VTXS        REG32(0x04000504)
#define reg_G3_POLYGON_ATTR    REG32(0x040004a4)
#define reg_G3_TEXIMAGE_PARAM  REG32(0x040004a8)
#define reg_G3_TEXPLTT_BASE    REG32(0x040004ac)
#define reg_G3X_GXSTAT         REG32(0x04000600)

extern void G3X_ClearFifo(void);
extern void G3X_InitMtxStack(void);
extern void G3X_InitTable(void);

static inline BOOL G3X_IsGeometryBusy(void)
{
    return (BOOL)(reg_G3X_GXSTAT & 0x08000000);
}

static inline void G3_End(void)
{
    reg_G3_END_VTXS = 0;
}

static inline void G3X_ResetListRamOverflow(void)
{
    reg_GX_DISP3DCNT |= 0x2000;
}

static inline void G3X_ResetLineBufferUnderflow(void)
{
    reg_GX_DISP3DCNT |= 0x1000;
}

static inline void G3X_SetShadingToon(void)
{
    reg_GX_DISP3DCNT = (u16)(reg_GX_DISP3DCNT & ~(0x0002 | 0x1000 | 0x2000));
}

static inline void G3X_AntiAliasOn(void)
{
    reg_GX_DISP3DCNT = (u16)((reg_GX_DISP3DCNT & ~(0x1000 | 0x2000)) | 0x0010);
}

static inline void G3X_AlphaTestOff(void)
{
    reg_GX_DISP3DCNT =
        (u16)(reg_GX_DISP3DCNT & (u16)~(0x0004 | 0x1000 | 0x2000));
}

static inline void G3X_ResetMtxStackOverflow(void)
{
    reg_G3X_GXSTAT |= 0x00008000;
}

static inline void G3X_SetFifoIntrCondEmpty(void)
{
    reg_G3X_GXSTAT = (reg_G3X_GXSTAT & ~0xc0000000) | 0x80000000;
}

static inline void G2_SetBG0Priority(int priority)
{
    reg_G2_BG0CNT = (u16)((reg_G2_BG0CNT & ~3) | priority);
}

void G3X_Init(void)
{
    G3X_ClearFifo();
    G3_End();

    while (G3X_IsGeometryBusy()) {
    }

    reg_GX_DISP3DCNT = 0;
    reg_G3X_GXSTAT = 0;
    reg_G2_BG0OFS = 0;

    G3X_ResetListRamOverflow();
    G3X_ResetLineBufferUnderflow();
    G3X_SetShadingToon();
    G3X_AntiAliasOn();
    G3X_AlphaTestOff();
    G3X_ResetMtxStackOverflow();
    G3X_SetFifoIntrCondEmpty();
    G3X_InitMtxStack();

    reg_G3X_CLEAR_COLOR = 0;
    reg_G3X_CLEAR_DEPTH = 0x7fff;
    reg_G3X_CLRIMAGE_OFFSET = 0;
    reg_G3X_FOG_COLOR = 0;
    reg_G3X_FOG_OFFSET = 0;

    G2_SetBG0Priority(0);
    G3X_InitTable();

    reg_G3_POLYGON_ATTR = 0x001f0080;
    reg_G3_TEXIMAGE_PARAM = 0;
    reg_G3_TEXPLTT_BASE = 0;
}
