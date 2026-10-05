#include "nitro/types.h"

extern u32 data_ov030_020bd020;
extern s32 Panel_TryBeginTransition4(void);
extern void SuspendTaskAndSetFlag(void);
extern void func_ov001_020828d4(void);
extern s32 func_ov001_0206dc38(void);
extern void func_ov001_0206de40(s32 index);
extern u32 func_ov001_0206dc4c(s32 index);
extern u32 GetBiasAdjustedField(s32 index);
extern void StoreSessionSpawnPoint(s32 index, u32 a, u32 b);
extern void func_ov001_020685d4(void);
extern void func_ov001_020676c4(void);
extern void func_ov001_0207ef68(u32 arg);
extern void func_ov001_0207efa0(void);
extern void func_ov001_0207d680(void);
extern void PopVramState(void);
extern void ActorRegistry_ClearCollisionResult(void);
extern void ReleaseSeqArcHeapLevel(u32 level);
extern void SetStreamVolumePercent(u32 percent);
extern void StoreToGlobalPtr4Field28(u32 value);

u32 MoviePlayer_Stop(void)
{
    s32 ready;
    u32 valueA;
    u32 valueB;
    s32 index;

    if (((*(u16 *)(data_ov030_020bd020 + 6) & 0x10) == 0) &&
        (ready = Panel_TryBeginTransition4(), ready == 0)) {
        return 0xffffffff;
    }
    SuspendTaskAndSetFlag();
    func_ov001_020828d4();
    index = 0;
    ready = func_ov001_0206dc38();
    if (0 < ready) {
        do {
            func_ov001_0206de40(index);
            valueA = func_ov001_0206dc4c(index);
            valueB = GetBiasAdjustedField(index);
            StoreSessionSpawnPoint(index, valueA, valueB);
            index = index + 1;
            ready = func_ov001_0206dc38();
        } while (index < ready);
    }
    func_ov001_020685d4();
    func_ov001_020676c4();
    func_ov001_0207ef68(1);
    func_ov001_0207efa0();
    *(u16 *)(data_ov030_020bd020 + 6) = *(u16 *)(data_ov030_020bd020 + 6) & 0xfff3;
    func_ov001_0207d680();
    PopVramState();
    ActorRegistry_ClearCollisionResult();
    ReleaseSeqArcHeapLevel(1);
    SetStreamVolumePercent(100);
    StoreToGlobalPtr4Field28(1);
    *(u16 *)(data_ov030_020bd020 + 6) = *(u16 *)(data_ov030_020bd020 + 6) | 0x8000;
    return 0x12;
}
