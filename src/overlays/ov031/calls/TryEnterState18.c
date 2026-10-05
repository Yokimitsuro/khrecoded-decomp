#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern void StoreToGlobalPtr4Field28(u32 a);
extern void ActorRegistry_ClearCollisionResult(void);
extern void PopVramState(void);
extern void ReleaseSeqArcHeapLevel(u32 index);
extern void StoreSessionSpawnPoint(u32 index, u32 a, u32 b);
extern void SuspendTaskAndSetFlag(void);
extern void func_ov001_020676c4(void);
extern void func_ov001_020685d4(void);
extern void GetBoundedEntryField(u32 index);
extern u32 func_ov001_0206dc38(void);
extern u32 func_ov001_0206dc4c(u32 index);
extern u32 GetBiasAdjustedField(u32 index);
extern void func_ov001_0206de40(u32 index);
extern u32 Panel_TryBeginTransition4(void);
extern void func_ov001_0207d680(void);
extern void func_ov001_0207ef68(u32 a);
extern void func_ov001_0207efa0(void);
extern void func_ov001_020828d4(void);
extern void func_ov059_020cbdf0(void);

u32 TryEnterState18(void)
{
    int result;
    u32 a;
    u32 b;
    int index;

    if ((data_ov031_020bc820->flags & 0x10) == 0) {
        result = Panel_TryBeginTransition4();
        if (result == 0) {
            return 0xffffffff;
        }
    }
    SuspendTaskAndSetFlag();
    func_ov001_020828d4();
    index = 0;
    result = func_ov001_0206dc38();
    if (0 < result) {
        do {
            GetBoundedEntryField(index);
            func_ov059_020cbdf0();
            func_ov001_0206de40(index);
            a = func_ov001_0206dc4c(index);
            b = GetBiasAdjustedField(index);
            StoreSessionSpawnPoint(index, a, b);
            index = index + 1;
            result = func_ov001_0206dc38();
        } while (index < result);
    }
    func_ov001_020685d4();
    func_ov001_020676c4();
    func_ov001_0207ef68(1);
    func_ov001_0207efa0();
    data_ov031_020bc820->flags = data_ov031_020bc820->flags & 0xfff3;
    func_ov001_0207d680();
    PopVramState();
    ActorRegistry_ClearCollisionResult();
    ReleaseSeqArcHeapLevel(1);
    StoreToGlobalPtr4Field28(1);
    data_ov031_020bc820->flags = data_ov031_020bc820->flags | 0x8000;
    return 0x12;
}
