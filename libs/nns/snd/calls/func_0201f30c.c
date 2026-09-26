typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000


#define SND_COMMAND_BLOCK (1 << 0)

BOOL func_0200f094(u32 flags);
void SND_WaitForCommandProc(u32 tag);
u32 func_0200f29c(void);

/* func_0201f30c -- NitroSystem heap.c: EraseSync. */
void func_0201f30c (void)
{
    u32 commandTag;

    commandTag = func_0200f29c();
    (void)func_0200f094(SND_COMMAND_BLOCK);
    SND_WaitForCommandProc(commandTag);
}
