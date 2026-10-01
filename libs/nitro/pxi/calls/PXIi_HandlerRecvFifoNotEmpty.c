#include "libs/nitro/pxi/pxi_fifo_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);

#define PXI_FIFO_COUNT (*(volatile u16 *)0x04000184)
#define PXI_SEND_FIFO (*(volatile u32 *)0x04000188)
#define PXI_RECV_FIFO (*(volatile u32 *)0x04100000)
#define PXI_FIFO_ERROR 0x4000
#define PXI_FIFO_ENABLE 0x8000
#define PXI_FIFO_SEND_FULL 0x0002
#define PXI_FIFO_RECV_EMPTY 0x0100
#define PXI_FIFO_SUCCESS 0
#define PXI_FIFO_FAIL_SEND_ERROR (-1)
#define PXI_FIFO_FAIL_SEND_FULL (-2)
#define PXI_FIFO_FAIL_RECV_ERROR (-3)
#define PXI_FIFO_FAIL_RECV_EMPTY (-4)

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

static inline int PXIi_GetFromFifo(u32 *data)
{
    OSIntrMode interruptMode;

    if (PXI_FIFO_COUNT & PXI_FIFO_ERROR) {
        PXI_FIFO_COUNT |= PXI_FIFO_ENABLE | PXI_FIFO_ERROR;
        return PXI_FIFO_FAIL_RECV_ERROR;
    }

    interruptMode = OS_DisableInterrupts();
    if (PXI_FIFO_COUNT & PXI_FIFO_RECV_EMPTY) {
        (void)OS_RestoreInterrupts(interruptMode);
        return PXI_FIFO_FAIL_RECV_EMPTY;
    }

    *data = PXI_RECV_FIFO;
    (void)OS_RestoreInterrupts(interruptMode);
    return PXI_FIFO_SUCCESS;
}

void PXIi_HandlerRecvFifoNotEmpty(void)
{
    PXIFifoMessage message;
    int result;
    int tag;

    while (1) {
        result = PXIi_GetFromFifo(&message.raw);
        if (result == PXI_FIFO_FAIL_RECV_EMPTY) {
            break;
        }
        if (result == PXI_FIFO_FAIL_RECV_ERROR) {
            continue;
        }

        tag = message.fields.tag;
        if (tag != 0) {
            if (FifoRecvCallbackTable[tag] != 0) {
                FifoRecvCallbackTable[tag](tag, message.fields.data, message.fields.error);
            } else if (!message.fields.error) {
                message.fields.error = 1;
                (void)PXIi_SetToFifo(message.raw);
            }
        }
    }
}
