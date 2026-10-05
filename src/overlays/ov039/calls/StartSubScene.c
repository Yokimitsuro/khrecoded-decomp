#include "nitro/types.h"

extern int data_ov039_020bea20;
extern int func_ov039_020bd644(void);
extern void RuntimeState_SetMode(int phase);
extern void func_ov039_020bacdc(int blockCount, u32 flag);
extern void SetMenuButtonsEnabled(BOOL enable);

void StartSubScene(int sceneId, int fadeFrames, BOOL markPending)
{
    int active = func_ov039_020bd644();
    int base = data_ov039_020bea20;

    *(int *)(base + 0xc9bc) = sceneId;
    if (active == -1) {
        RuntimeState_SetMode(1);
        *(int *)(base + 0xca0c) = 1;
        return;
    }
    if (fadeFrames < 0) {
        fadeFrames = 100;
    }
    *(u8 *)(base + 0xca44) = 1;
    RuntimeState_SetMode(4);
    func_ov039_020bacdc(-16, fadeFrames);
    SetMenuButtonsEnabled(FALSE);
    if (markPending) {
        *(int *)(base + 0xca0c) = 1;
    }
    *(u16 *)(base + 0xca70) = 0;
    *(u16 *)(base + 0xca6e) = 0;
    *(u16 *)(base + 0xca6c) = 0;
}
