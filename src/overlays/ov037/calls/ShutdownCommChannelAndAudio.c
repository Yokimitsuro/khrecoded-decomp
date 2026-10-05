#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x14];
    s32 handle;
} CommState;

extern CommState *gContinueSceneState;
extern void SetSoundListenersEnabled(int enabled);
extern void func_ov001_0206a714(void);
extern void func_ov001_02063c54(void);
extern void SetParamHalf18(u16 value);
extern void SetParamWord20(int value);

void ShutdownCommChannelAndAudio(void)
{
    SetSoundListenersEnabled(0);
    if (gContinueSceneState->handle != -1) {
        func_ov001_0206a714();
        gContinueSceneState->handle = -1;
    }
    func_ov001_02063c54();
    SetParamHalf18(0);
    SetParamWord20(0);
    gContinueSceneState = 0;
}
