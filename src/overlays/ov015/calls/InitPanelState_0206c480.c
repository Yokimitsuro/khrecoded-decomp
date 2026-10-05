#include "nitro/types.h"

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, int val, u32 size);
extern void func_ov015_0206c708(void);
extern void func_ov015_02070af8(int param);
extern void *data_ov015_0207e960;

void InitPanelState_0206c480(void) {
    int size = 0xdec4;
    s8 zero = 0;
    data_ov015_0207e960 = NNSi_FndAllocFromDefaultHeap(size);
    MI_CpuFill8(data_ov015_0207e960, zero, size);
    ((s8 *)data_ov015_0207e960)[0] = zero - 1;
    ((s8 *)data_ov015_0207e960)[1] = zero;
    func_ov015_0206c708();
    func_ov015_02070af8(zero);
}
