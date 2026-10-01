#ifndef NITRO_PXI_FIFO_INTERNAL_H
#define NITRO_PXI_FIFO_INTERNAL_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
typedef u32 OSIntrMode;
typedef void (*PXIFifoCallback)(int tag, u32 data, BOOL error);

typedef struct OSSystemWork {
    u8 reserved[0x388];
    u32 pxiHandleChecker[2];
} OSSystemWork;

typedef union PXIFifoMessage {
    struct {
        u32 tag : 5;
        u32 error : 1;
        u32 data : 26;
    } fields;
    u32 raw;
} PXIFifoMessage;

extern u16 FifoCtrlInit;
extern PXIFifoCallback FifoRecvCallbackTable[32];

void PXI_InitFifo(void);
int PXI_SendWordByFifo(int tag, u32 data, BOOL error);
void PXIi_HandlerRecvFifoNotEmpty(void);

#endif
