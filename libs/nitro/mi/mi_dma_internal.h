#ifndef NITRO_MI_DMA_INTERNAL_H
#define NITRO_MI_DMA_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef volatile u32 vu32;
typedef void (*MIDmaCallback)(void *arg);
typedef void (*OSIrqFunction)(void);

typedef enum GXFifoIntrCond {
    GX_FIFOINTR_COND_DISABLE = 0,
    GX_FIFOINTR_COND_UNDERHALF = 1,
    GX_FIFOINTR_COND_EMPTY = 2
} GXFifoIntrCond;

typedef union MIiDmaClearSource {
    u32 word;
    u16 halfword;
} MIiDmaClearSource;

typedef struct MIiGXDmaParams {
    volatile BOOL isBusy;
    u32 dmaNo;
    u32 src;
    u32 length;
    MIDmaCallback callback;
    void *arg;
    GXFifoIntrCond fifoCond;
    OSIrqFunction fifoFunc;
} MIiGXDmaParams;

extern MIiGXDmaParams MIi_GXDmaParams;

enum {
    MI_DMA_MAX_NUM = 3,
    MI_DMA_CHANNEL_STRIDE = 12,
    MI_DMA_CONTROL_OFFSET = 8,
    MIi_GX_LENGTH_ONCE = 118 * sizeof(u32)
};

#define MI_DMA_REGISTER_BASE 0x040000b0
#define MI_DMA_CLEAR_DATA_BASE 0x040000e0
#define MI_DMA_TIMING_MASK 0x3a000000
#define MI_DMA_TIMING_ONLY_MASK 0x38000000
#define MI_DMA_ENABLE 0x80000000
#define MI_DMA0_CLEAR_DATA 0x81400001

#define MI_DMA_TIMING_V_BLANK 0x08000000
#define MI_DMA_TIMING_H_BLANK 0x10000000
#define MI_DMA_TIMING_DISP 0x18000000
#define MI_DMA_TIMING_DISP_MMEM 0x20000000
#define MI_DMA_TIMING_CARD 0x28000000
#define MI_DMA_TIMING_CARTRIDGE 0x30000000
#define MI_DMA_TIMING_GXFIFO 0x38000000
#define MI_DMA_TIMING_ANY (~0U)
#define MI_DMA_SRC_INC 0
#define MI_DMA_SRC_FIX 0x01000000

#define MIi_DMA_MODE_NOINT 0x01
#define MIi_DMA_MODE_WAIT 0x02
#define MIi_DMA_MODE_NOCLEAR 0x04
#define MIi_DMA_MODE_SRC32 0x10
#define MIi_DMA_MODE_SRC16 0x20

#define MI_CNT_CLEAR32(size) (0x85000000 | ((size) / 4))
#define MI_CNT_SET_CLEAR32(size) (0x05000000 | ((size) / 4))
#define MI_CNT_COPY32(size) (0x84000000 | ((size) / 4))
#define MI_CNT_SET_COPY32(size) (0x04000000 | ((size) / 4))
#define MI_CNT_COPY16(size) (0x80000000 | ((size) / 2))
#define MI_CNT_SET_COPY16(size) ((size) / 2)
#define MI_CNT_CLEAR32_IF(size) (0xc5000000 | ((size) / 4))
#define MI_CNT_SET_CLEAR32_IF(size) (0x45000000 | ((size) / 4))
#define MI_CNT_COPY32_IF(size) (0xc4000000 | ((size) / 4))
#define MI_CNT_SET_COPY32_IF(size) (0x44000000 | ((size) / 4))
#define MI_CNT_SEND32(size) (0x84400000 | ((size) / 4))
#define MI_CNT_SEND32_IF(size) (0xc4400000 | ((size) / 4))
#define MI_CNT_GXCOPY_IF(size) (0xfc400000 | ((size) / 4))
#define MI_CNT_CARDRECV32_CONTINUOUS 0xaf000001

#define MI_DMA_CONTROL(dmaNo) \
    (&((vu32 *)MI_DMA_REGISTER_BASE)[(dmaNo) * 3 + 2])

#define REG_GXFIFO_ADDR 0x04000400
#define REG_G3X_GXSTAT (*(vu32 *)0x04000600)
#define REG_G3X_GXSTAT_FIFOSTAT_MASK 0x07000000
#define REG_G3X_GXSTAT_FIFOSTAT_SHIFT 24
#define REG_G3X_GXSTAT_FI_MASK 0xc0000000
#define REG_G3X_GXSTAT_FI_SHIFT 30
#define GX_FIFOSTAT_UNDERHALF 2
#define OS_IE_GXFIFO 0x00200000

OSIntrMode OS_DisableInterrupts(void);
OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);
u32 OS_EnableIrqMask(u32 mask);
u32 OS_DisableIrqMask(u32 mask);
u32 OS_ResetRequestIrqMask(u32 mask);
OSIrqFunction OS_GetIrqFunction(u32 mask);
void OS_SetIrqFunction(u32 mask, OSIrqFunction function);
void OS_Terminate(void);
void OSi_EnterDmaCallback(u32 dmaNo, MIDmaCallback callback, void *arg);

void MIi_DmaSetParameters(
    u32 dmaNo, u32 source, u32 destination, u32 control, u32 mode);
void MIi_DmaFill32(
    u32 dmaNo, void *destination, u32 data, u32 size, BOOL dmaEnable);
void MIi_DmaCopy32(
    u32 dmaNo, const void *source, void *destination, u32 size, BOOL dmaEnable);
void MIi_DmaCopy16(
    u32 dmaNo, const void *source, void *destination, u32 size, BOOL dmaEnable);
void MIi_DmaFill32Async(
    u32 dmaNo, void *destination, u32 data, u32 size,
    MIDmaCallback callback, void *arg, BOOL dmaEnable);
void MIi_DmaCopy32Async(
    u32 dmaNo, const void *source, void *destination, u32 size,
    MIDmaCallback callback, void *arg, BOOL dmaEnable);

void MIi_CheckAnotherAutoDMA(u32 dmaNo, u32 dmaType);
void MIi_CheckDma0SourceAddress(
    u32 dmaNo, u32 source, u32 size, u32 direction);
void MI_WaitDma(u32 dmaNo);
void MI_StopDma(u32 dmaNo);
void MI_StopAllDma(void);

void MI_SendGXCommandAsync(
    u32 dmaNo, const void *src, u32 commandLength,
    MIDmaCallback callback, void *arg);
void MIi_FIFOCallback(void);
void MIi_DMACallback(void *unused);
void MI_SendGXCommandAsyncFast(
    u32 dmaNo, const void *src, u32 commandLength,
    MIDmaCallback callback, void *arg);
void MIi_DMAFastCallback(void *unused);
void MIi_CardDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);

#endif
