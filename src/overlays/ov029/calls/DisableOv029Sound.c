#include "nitro/types.h"

extern u32 data_ov029_020babc0;
extern void func_ov001_0206de40();
extern u32 func_ov001_0206dc4c();
extern u32 GetBiasAdjustedField();
extern void StoreSessionSpawnPoint();
extern u32 func_ov001_0206dc38();
extern void func_ov001_020685d4();
extern void func_ov001_020676c4();
extern void func_ov001_0207ef68();
extern void func_ov001_0207efa0();
extern void func_ov001_0207d680();
extern void PopVramState();
extern void ActorRegistry_ClearCollisionResult();
extern void ReleaseSeqArcHeapLevel();
extern void StoreToGlobalPtr4Field28();

int DisableOv029Sound(void)
{
    s32 index;
    s32 count;
    u32 volume;
    u32 pan;

    index = 0;
    count = func_ov001_0206dc38();
    if (0 < count) {
        do {
            func_ov001_0206de40(index);
            volume = func_ov001_0206dc4c(index);
            pan = GetBiasAdjustedField(index);
            StoreSessionSpawnPoint(index, volume, pan);
            index = index + 1;
            count = func_ov001_0206dc38();
        } while (index < count);
    }
    func_ov001_020685d4();
    func_ov001_020676c4();
    func_ov001_0207ef68(1);
    func_ov001_0207efa0();
    *(u16 *)(data_ov029_020babc0 + 6) = *(u16 *)(data_ov029_020babc0 + 6) & 0xfff3;
    func_ov001_0207d680();
    PopVramState();
    ActorRegistry_ClearCollisionResult();
    ReleaseSeqArcHeapLevel(1);
    StoreToGlobalPtr4Field28(1);
    *(u16 *)(data_ov029_020babc0 + 6) = *(u16 *)(data_ov029_020babc0 + 6) | 0x8000;
    return 7;
}
