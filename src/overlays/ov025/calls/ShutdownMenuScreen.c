#include "nitro/types.h"

extern u32 data_ov025_020b7780;
extern u32 sOv025_Ocuitask_020b775c;

extern void NotifyBothOrOne(u32 a, u32 b, int index);
extern void SetWidgetRootTouchEnabled(u32 ctx, u32 enable);
extern void CloseSlotListView(u32 list);
extern void DestroyObjectsAndRelease(u32 ctx);
extern void func_ov027_020b7e1c(u32 ctx);
extern void FreeAllocatedBuffers(u32 buffers);
extern BOOL DestroyFndObjectList(u32 container);
extern u32 func_ov001_0207b228(u32 arg);

void ShutdownMenuScreen(void)
{
    u32 ctx = data_ov025_020b7780;

    NotifyBothOrOne(1, (u32)&sOv025_Ocuitask_020b775c, -1);
    SetWidgetRootTouchEnabled(ctx + 0x4c, 0);
    CloseSlotListView(ctx + 0x64f4);
    DestroyObjectsAndRelease(ctx + 0x4c);
    func_ov027_020b7e1c(ctx);
    *(u32 *)(ctx + 0x64e4) = 0;
    FreeAllocatedBuffers(ctx + 0x64c8);
    DestroyFndObjectList(ctx + 0x669c);
    DestroyFndObjectList(ctx + 0x6668);
    DestroyFndObjectList(ctx + 0x6634);
    func_ov001_0207b228(0);
    *(vu32 *)0x04001018 = 0;
    *(vu32 *)0x0400101c = 0;
}
