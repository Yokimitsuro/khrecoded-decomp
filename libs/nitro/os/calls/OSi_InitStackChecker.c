typedef unsigned char u8;
typedef unsigned int u32;

extern u8 data_027e0000[];
extern void SDK_IRQ_STACKSIZE(void);

#define HW_DTCM_IRQ_STACK_END ((u32)data_027e0000 + 0x3f80)
#define OS_IRQ_STACK_BOTTOM HW_DTCM_IRQ_STACK_END
#define OS_IRQ_STACK_TOP (OS_IRQ_STACK_BOTTOM - (u32)SDK_IRQ_STACKSIZE)
#define OS_IRQ_STACK_CHECKNUM_BOTTOM 0xfddb597dUL
#define OS_IRQ_STACK_CHECKNUM_TOP 0x7bf9dd5bUL

void OSi_InitStackChecker(void)
{
    *(u32 *)(OS_IRQ_STACK_BOTTOM - 4) = OS_IRQ_STACK_CHECKNUM_BOTTOM;
    *(u32 *)OS_IRQ_STACK_TOP = OS_IRQ_STACK_CHECKNUM_TOP;
}