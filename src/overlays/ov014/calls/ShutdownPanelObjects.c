#include "nitro/types.h"

extern u32 data_ov014_0206f9a0;
extern void func_ov027_020b7e1c(u32 panel);
extern void FreeAllocatedBuffers(u32 panel);
extern void DestroyObjectsAndRelease(u32 panel);
extern void ZeroHalfThenFree(void *block);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void ReleaseRecordSlot(s32 mode);

void ShutdownPanelObjects(void)
{
    func_ov027_020b7e1c(data_ov014_0206f9a0);
    func_ov027_020b7e1c(data_ov014_0206f9a0 + 0x4c);
    FreeAllocatedBuffers(data_ov014_0206f9a0 + 0xc990);
    DestroyObjectsAndRelease(data_ov014_0206f9a0 + 0x98);
    DestroyObjectsAndRelease(data_ov014_0206f9a0 + 0x6514);
    ZeroHalfThenFree(*(void **)(data_ov014_0206f9a0 + 0xcab4));
    NNSi_FndFreeFromDefaultHeap(*(void **)(data_ov014_0206f9a0 + 0xcab8));
    NNSi_FndFreeFromDefaultHeap(*(void **)(data_ov014_0206f9a0 + 0xcabc));
    NNSi_FndFreeFromDefaultHeap((void *)data_ov014_0206f9a0);
    ReleaseRecordSlot(9);
    ReleaseRecordSlot(10);
}
