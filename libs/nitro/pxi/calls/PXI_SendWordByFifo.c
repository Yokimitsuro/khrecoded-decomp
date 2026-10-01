#include "libs/nitro/pxi/pxi_fifo_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);

#define PXI_FIFO_COUNT (*(volatile u16 *)0x04000184)
#define PXI_SEND_FIFO (*(volatile u32 *)0x04000188)
#define PXI_FIFO_ERROR 0x4000
#define PXI_FIFO_ENABLE 0x8000
#define PXI_FIFO_SEND_FULL 0x0002
#define PXI_FIFO_SUCCESS 0
#define PXI_FIFO_FAIL_SEND_ERROR (-1)
#define PXI_FIFO_FAIL_SEND_FULL (-2)

static inline int PXIi_SetToFifo(u32 data)
{
    OSIntrMode interruptMode;

    if (PXI_FIFO_COUNT & PXI_FIFO_ERROR) {
        PXI_FIFO_COUNT |= PXI_FIFO_ENABLE | PXI_FIFO_ERROR;
        return PXI_FIFO_FAIL_SEND_ERROR;
    }

    interruptMode = OS_DisableInterrupts();
    if (PXI_FIFO_COUNT & PXI_FIFO_SEND_FULL) {
        (void)OS_RestoreInterrupts(interruptMode);
        return PXI_FIFO_FAIL_SEND_FULL;
    }

    PXI_SEND_FIFO = data;
    (void)OS_RestoreInterrupts(interruptMode);
    return PXI_FIFO_SUCCESS;
}

int PXI_SendWordByFifo(int tag, u32 data, BOOL error)
{
    PXIFifoMessage message;

    message.fields.tag = tag;
    message.fields.error = error;
    message.fields.data = data;
    return PXIi_SetToFifo(message.raw);
}
