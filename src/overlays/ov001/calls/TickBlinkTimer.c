#include "nitro/types.h"

typedef struct RecordPool RecordPool;

typedef struct BlinkState {
    u8 pad_00[0x24];
    u16 timer;
    u8 pad_26[2];
    u32 flags;
    u8 pad_2C[8];
    int vramOffset;
} BlinkState;

extern RecordPool *GetSceneTagTracker(void);
extern int NNS_GfdRegisterNewVramTransferTask(int command, int value, int address, int size);
extern void *FindActiveRecordById(RecordPool *pool, u32 recordId);
extern void func_ov027_020b8288(RecordPool *pool, void *record);

void TickBlinkTimer(BlinkState *blink)
{
    RecordPool *pool = GetSceneTagTracker();

    if (blink->timer == 0) {
        return;
    }
    if (blink->timer >= 6) {
        NNS_GfdRegisterNewVramTransferTask(0xf, 0x1c2, blink->vramOffset + 2, 0xe);
        blink->timer = 0;
        blink->flags |= 2;
        func_ov027_020b8288(pool, FindActiveRecordById(pool, 0x137));
    } else {
        blink->timer++;
    }
}
