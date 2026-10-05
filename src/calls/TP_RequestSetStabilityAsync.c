#include "nitro/types.h"

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern s32 PXI_SendWordByFifo(u32 a, u32 b, u32 c);

typedef void (*Callback)(u32, u32, u32);

struct Data {
    u32 unk00;
    Callback cb;
    u32 pad08[12];
    u16 unk38;
    u16 unk3a;
};

extern struct Data data_02059784;

void TP_RequestSetStabilityAsync(u32 unused, u32 arg) {
    u32 ie = OS_DisableInterrupts();
    BOOL ok = PXI_SendWordByFifo(6, arg | 0x3000300, 0) >= 0;
    if (!ok) {
        OS_RestoreInterrupts(ie);
        data_02059784.unk38 |= 8;
        if (data_02059784.cb != 0) {
            data_02059784.cb(3, 4, 0);
        }
        return;
    }
    data_02059784.unk3a |= 8;
    data_02059784.unk38 &= ~8;
    OS_RestoreInterrupts(ie);
}
