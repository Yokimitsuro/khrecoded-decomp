#ifndef NITRO_MI_DMA_INTERNAL_H
#define NITRO_MI_DMA_INTERNAL_H

typedef unsigned int u32;
typedef int OSIntrMode;
typedef volatile unsigned int vu32;

#define MI_DMA_REGISTER_BASE 0x040000b0
#define MI_DMA_CHANNEL_STRIDE 12
#define MI_DMA_CONTROL_OFFSET 8
#define MI_DMA_TIMING_MASK 0x3a000000
#define MI_DMA_ENABLE 0x80000000
#define MI_DMA0_CLEAR_DATA 0x81400001

OSIntrMode OS_DisableInterrupts(void);
OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);
void MI_WaitDma(u32 dmaNo);
void MI_StopDma(u32 dmaNo);
void MI_StopAllDma(void);

#endif