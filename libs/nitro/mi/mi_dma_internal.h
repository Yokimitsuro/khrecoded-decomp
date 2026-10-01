#ifndef NITRO_MI_DMA_INTERNAL_H
#define NITRO_MI_DMA_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef volatile u32 vu32;
typedef void (*MIDmaCallback)(void *arg);

typedef union MIiDmaClearSource {
    u32 word;
    u16 halfword;
} MIiDmaClearSource;

enum {
    MI_DMA_CHANNEL_STRIDE = 12,
    MI_DMA_CONTROL_OFFSET = 8
};

#define MI_DMA_REGISTER_BASE 0x040000b0
#define MI_DMA_CLEAR_DATA_BASE 0x040000e0
#define MI_DMA_TIMING_MASK 0x3a000000
#define MI_DMA_ENABLE 0x80000000
#define MI_DMA0_CLEAR_DATA 0x81400001

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

#define MI_DMA_CONTROL(dmaNo)     (&((vu32 *)MI_DMA_REGISTER_BASE)[(dmaNo) * 3 + 2])

OSIntrMode OS_DisableInterrupts(void);
OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);
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

void MIi_CheckDma0SourceAddress(
    u32 dmaNo, u32 source, u32 size, u32 direction);
void MI_WaitDma(u32 dmaNo);
void MI_StopDma(u32 dmaNo);
void MI_StopAllDma(void);

#endif
