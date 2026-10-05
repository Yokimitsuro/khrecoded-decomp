#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x20e];
    s16 pendingScene;
} Session;

extern u8 *data_0205fe0c;
extern Session *data_ov001_020a0480;
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern int ReadGlobalPackedBits(int bitOffset, int bitCount);
extern void func_ov001_0206317c(int sceneId, int subSceneId, int mode, int param);
extern void func_ov001_020645dc(int bitOffset);

void EnterSceneSlot(int slot, BOOL reset)
{
    int sceneId = (slot + 1) * 100;

    if (reset) {
        MIi_CpuClearFast(0, data_0205fe0c + 0x840, 0x1e0);
        func_ov001_0206317c(sceneId, 0, 1, 1);
        data_ov001_020a0480->pendingScene = -1;
        return;
    }
    func_ov001_0206317c(sceneId, ReadGlobalPackedBits(0x4215, 10), 1, 1);
    func_ov001_020645dc(0x1a05);
}
