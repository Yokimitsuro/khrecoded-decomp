#include "nitro/types.h"

typedef struct WM9Buffer {
    u8 *wm7Buffer;
    u8 *status;
    u8 *pad_08;
    u8 *fifo9to7;
    u8 *fifo7to9;
    u16 dmaNo;
    u8 pad_16[0xcc - 0x16];
    void *callbacks[16];
    void *callbackArgs[16];
    u32 scanOnlyFlag;
    u16 connectedCount;
} WM9Buffer;

typedef struct WMiState {
    u16 initialized;
    u16 pad_02;
    WM9Buffer *buffer;
} WMiState;

extern WMiState data_020597fc;
extern u8 data_02059814[];
extern void *data_02059834[];
extern u16 data_020598a0[10][0x80];

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern BOOL OS_IsOnVram(void *addr);
extern void PXI_Init(void);
extern BOOL PXI_IsCallbackReady(int tag, int proc);
extern void DC_InvalidateRange(void *addr, u32 size);
extern void MIi_DmaFill32(u32 dmaNo, void *dest, u32 data, u32 size, BOOL sync);
extern void Ov105_ClearSharedRequestBit(void);
extern void OS_InitMessageQueue(void *queue, void **messages, int count);
extern void DC_StoreRange(void *addr, u32 size);
extern BOOL OS_SendMessage(void *queue, void *message, int flags);
extern void PXI_SetFifoRecvCallback(int tag, void *callback);
extern void WmReceiveFifo(void);

static inline void DmaClear32(u32 dmaNo, void *dest, u32 size)
{
    MIi_DmaFill32(dmaNo, dest, 0, size, TRUE);
}

#pragma opt_rotateloops off
#pragma opt_common_subs off
int WMi_InitCore(void *buffer, u16 dmaNo, u32 size)
{
    int enabled = OS_DisableInterrupts();
    int i;

    if (data_020597fc.initialized) {
        OS_RestoreInterrupts(enabled);
        return 3;
    }
    if (buffer == NULL) {
        OS_RestoreInterrupts(enabled);
        return 6;
    }
    if (OS_IsOnVram(buffer)) {
        OS_RestoreInterrupts(enabled);
        return 6;
    }
    if (dmaNo > 3) {
        OS_RestoreInterrupts(enabled);
        return 6;
    }
    if ((u32)buffer & 0x1f) {
        OS_RestoreInterrupts(enabled);
        return 6;
    }
    PXI_Init();
    if (!PXI_IsCallbackReady(10, 1)) {
        OS_RestoreInterrupts(enabled);
        return 4;
    }
    DC_InvalidateRange(buffer, size);
    DmaClear32(dmaNo, buffer, size);
    data_020597fc.buffer = buffer;
    data_020597fc.buffer->wm7Buffer = (u8 *)buffer + 0x200;
    data_020597fc.buffer->status = data_020597fc.buffer->wm7Buffer + 0x300;
    data_020597fc.buffer->fifo9to7 = data_020597fc.buffer->status + 0x800;
    data_020597fc.buffer->fifo7to9 = data_020597fc.buffer->fifo9to7 + 0x100;
    Ov105_ClearSharedRequestBit();
    data_020597fc.buffer->dmaNo = dmaNo;
    data_020597fc.buffer->scanOnlyFlag = 0;
    data_020597fc.buffer->connectedCount = 0;
    for (i = 0; i < 16; i++) {
        data_020597fc.buffer->callbacks[i] = NULL;
        data_020597fc.buffer->callbackArgs[i] = NULL;
    }
    OS_InitMessageQueue(data_02059814, data_02059834, 10);
    for (i = 0; i < 10; i++) {
        data_020598a0[i][0] = 0x8000;
        DC_StoreRange(data_020598a0[i], 2);
        OS_SendMessage(data_02059814, data_020598a0[i], 1);
    }
    PXI_SetFifoRecvCallback(10, WmReceiveFifo);
    data_020597fc.initialized = TRUE;
    OS_RestoreInterrupts(enabled);
    return 0;
}
#pragma opt_common_subs reset
#pragma opt_rotateloops reset
