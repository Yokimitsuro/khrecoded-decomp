#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x55];
    s8 slotIndex;
    s8 slotCounts[0x19];
    u8 enabled;
} SceneContext;

typedef struct {
    u8 pad_00[6];
    u16 flags;
} SceneState;

typedef struct {
    SceneContext *context;
    SceneState *scene;
} Ov032Globals;

extern Ov032Globals data_ov032_020c0080;
extern u32 func_ov001_02063620(void);
extern void PushVramState(void);
extern int func_ov001_02067ed4(void);
extern u32 func_ov001_020680cc(u32 index, u32 value);
extern u32 func_ov001_020680e4(u32 index, u32 value);

s32 SetSlotDisplayStyle(void) {
    SceneContext *context;
    if (func_ov001_02063620() != 0) {
        return -1;
    }
    PushVramState();
    context = data_ov032_020c0080.context;
    if (context->enabled) {
        if (context->slotCounts[context->slotIndex] > 0) {
            func_ov001_020680cc(func_ov001_02067ed4(), 0x18);
            func_ov001_020680e4(func_ov001_02067ed4(), 0x19);
        } else {
            func_ov001_020680cc(func_ov001_02067ed4(), 0x16);
            func_ov001_020680e4(func_ov001_02067ed4(), 0x17);
        }
    }
    data_ov032_020c0080.scene->flags |= 0x8000;
    return 1;
}
