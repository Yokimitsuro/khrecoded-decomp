#include "nitro/types.h"

extern u32 data_ov002_0206c464;
extern void FreePointerIfSet(u32 target);
extern void func_ov027_020b7e1c(u32 target);
extern void DestroyObjectsAndRelease(u32 target);
extern int ZeroHalfThenFree(void *ptr);
extern void NNSi_FndFreeFromDefaultHeap(u32 target);

void ReleaseContextResources(void) {
    FreePointerIfSet(data_ov002_0206c464 + 0xce64);
    func_ov027_020b7e1c(data_ov002_0206c464 + 0x520);
    func_ov027_020b7e1c(data_ov002_0206c464 + 0x4d4);
    DestroyObjectsAndRelease(data_ov002_0206c464 + 0x69e8);
    DestroyObjectsAndRelease(data_ov002_0206c464 + 0x56c);
    ZeroHalfThenFree((void *)*(u32 *)(data_ov002_0206c464 + 0x24));
    NNSi_FndFreeFromDefaultHeap(data_ov002_0206c464);
}
