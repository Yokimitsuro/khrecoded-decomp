typedef unsigned char u8;
typedef unsigned int u32;

typedef struct OSSystemWork {
    u8 reserved[0x388];
    u32 pxiHandleChecker[2];
} OSSystemWork;

int PXI_IsCallbackReady(int fifoTag, int processor)
{
    OSSystemWork *work = (OSSystemWork *)0x02fffc00;
    return (work->pxiHandleChecker[processor] & (1U << fifoTag)) ? 1 : 0;
}