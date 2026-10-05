#include "nitro/types.h"

typedef struct BoardState {
    int resourceA;
    int resourceB;
    void *widget;
    char pad000c[0x28 - 0xc];
    char animSet[0x74 - 0x28];
    char objectSet[0x64f0 - 0x74];
    void *listener;
    char pad64f4[0x66e0 - 0x64f4];
    int useChannel;
} BoardState;

extern BoardState *data_ov024_020b7540;
extern char sOv024_SYSMAPTASK_020b751c[];
extern void NotifyBothOrOne(int channel, void *target, int arg);
extern void FreeSceneListObject(void *listener);
extern void ReleaseOverlayResourceSlots(void);
extern void func_ov027_020b7e1c(void *animSet);
extern void DestroyObjectsAndRelease(void *objectSet);
extern void FreeAllocatedBuffers(void *widget);
extern void func_ov001_0207b228(int value);
extern void ZeroHalfThenFree(int handle);
extern void TeardownContextState(void);

void DestroyBoardScreen(void)
{
    if (data_ov024_020b7540->useChannel) {
        NotifyBothOrOne(1, sOv024_SYSMAPTASK_020b751c, 0);
    } else {
        FreeSceneListObject(data_ov024_020b7540->listener);
    }
    ReleaseOverlayResourceSlots();
    func_ov027_020b7e1c(data_ov024_020b7540->animSet);
    DestroyObjectsAndRelease(data_ov024_020b7540->objectSet);
    if (data_ov024_020b7540->useChannel) {
        FreeAllocatedBuffers(data_ov024_020b7540->widget);
    } else {
        func_ov001_0207b228(0);
    }
    ZeroHalfThenFree(data_ov024_020b7540->resourceA);
    ZeroHalfThenFree(data_ov024_020b7540->resourceB);
    TeardownContextState();
    data_ov024_020b7540 = NULL;
}
