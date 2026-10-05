#include "nitro/types.h"

typedef struct {
    u8 pad_00[9];
    u8 locked;
} SceneState;

extern SceneState *data_ov030_020bd020;

extern void func_ov042_020bd5f4(BOOL enabled);

void SetSceneLock(u8 locked) {
    data_ov030_020bd020->locked = locked;
    func_ov042_020bd5f4(locked == 0 ? TRUE : FALSE);
}
