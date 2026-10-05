#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void func_ov015_0207634c(void);
extern void *data_ov015_020812e0;

void ReleaseWorkBuffer(void) {
    func_ov015_0207634c();
    if (data_ov015_020812e0 == 0) {
        return;
    }
    NNSi_FndFreeFromDefaultHeap(data_ov015_020812e0);
    data_ov015_020812e0 = 0;
}
