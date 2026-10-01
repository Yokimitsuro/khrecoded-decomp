#include "src/overlays/ov104/calls/dsprot_main.h"

u32 DetectNotDummy(void *callback, void *param, u32 unused) {
#pragma unused(unused)
    u32 func_queue[32];

    func_queue[0] = ADDR_PLUS_ADDEND(RunEncrypted_Dummy_IsGood, ENC_VAL_1) + DSP_OBFS_OFFSET;
    func_queue[1] = FUNC_QUEUE_END;

    return dsprotMain(func_queue, DSPROT_EXPECT_TRUE, callback, param);
}
