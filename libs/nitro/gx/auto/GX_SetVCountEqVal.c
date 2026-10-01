typedef unsigned short u16;
typedef int s32;

#define REG_DISPSTAT (*(volatile u16 *)0x04000004)

void GX_SetVCountEqVal(s32 value)
{
    REG_DISPSTAT = (u16)((REG_DISPSTAT & 0x3f) |
                         ((value & 0xff) << 8) |
                         ((value & 0x100) >> 1));
}
