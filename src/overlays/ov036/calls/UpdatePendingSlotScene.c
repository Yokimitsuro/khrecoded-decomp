#include "nitro/types.h"

typedef struct SlotScene {
    u8 pad_0000[0x10cc];
    s32 isActive;
    u8 pad_10D0[0x4];
    s32 pendingA;
    s32 pendingB;
} SlotScene;

typedef struct SlotSceneHolder {
    u32 unk_00;
    SlotScene *scene;
} SlotSceneHolder;

extern SlotSceneHolder data_ov036_020c3940;
extern void func_ov036_020bad5c(void);

void UpdatePendingSlotScene(void)
{
    SlotScene *scene = data_ov036_020c3940.scene;

    if (scene->isActive == 0) {
        return;
    }
    if (scene->pendingA == 0 && scene->pendingB == 0) {
        return;
    }
    func_ov036_020bad5c();
}
