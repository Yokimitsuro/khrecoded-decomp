#include "nitro/types.h"

extern u32 data_ov029_020babc0;
extern void func_ov001_0207d148();
extern u32 func_ov001_02063a6c();
extern void func_ov021_020af59c();
extern void func_ov001_0207ef68();
extern void SetMenuHighlight();
extern u32 func_ov001_020645c8();
extern void func_ov001_0206e444();
extern void CacheSeqArcStatus();
extern void StoreToGlobalPtr4Field28();

int EnableOv029Sound(void)
{
    u16 flags;
    u32 ctx;
    u32 handle;
    u32 ready;

    ctx = data_ov029_020babc0;
    func_ov001_0207d148(1);
    handle = func_ov001_02063a6c();
    func_ov021_020af59c(handle, 0);
    func_ov001_0207ef68(0);
    SetMenuHighlight(0);
    ready = func_ov001_020645c8(0x3309);
    if (ready == 0) {
        func_ov001_0206e444(0);
    }
    *(u16 *)(data_ov029_020babc0 + 6) = *(u16 *)(data_ov029_020babc0 + 6) | 0xc;
    flags = *(u16 *)(ctx + 6);
    if ((flags & 1) != 0) {
        *(u16 *)(ctx + 6) = flags & 0xfffe;
    }
    CacheSeqArcStatus(2);
    StoreToGlobalPtr4Field28(0);
    return 5;
}
