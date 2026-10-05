#include "nitro/types.h"

extern void func_02052528(void *record, int value0, int value1, int value2, int value3);
extern void func_02052570(void *record);

void StartTimerFromPackedPair(void *record, u32 packed, int extra) {
    s16 high = (u16)(packed >> 16);
    s16 low = (u16)packed;
    func_02052528(record, 0, high * 0xcccd, low * 0xcccd, extra);
    func_02052570(record);
}
