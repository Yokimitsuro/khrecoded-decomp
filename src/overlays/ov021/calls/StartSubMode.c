#include "nitro/types.h"

typedef void *(*SubModeUpdateFunc)(void);

typedef struct SubModeState {
    s32 mode;
    void *block;
    SubModeUpdateFunc update;
    void **heap;
} SubModeState;

extern SubModeState *data_ov021_020b56c0;
extern s32 data_ov021_020b52b0[];

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MIi_CpuClear32(u32 value, void *dest, u32 size);
extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern void *NNSi_FndAllocFromExpHeapEx(u32 size, void **heap);
extern void func_02029f8c(int processor, int overlayId);
extern SubModeUpdateFunc func_ov046_020c08c0(void *arg, void *block);
extern SubModeUpdateFunc func_ov042_020bdb6c(void *arg, void *block);
extern SubModeUpdateFunc InitCameraState_020bcbec(void *arg, void *block);
extern SubModeUpdateFunc InitPanel(void *arg, void *block);

void StartSubMode(void *arg, void **heap, s32 mode)
{
    SubModeState initial;
    u32 blockSize;

    switch (mode) {
    case 0:
        blockSize = 0x414;
        break;
    case 1:
        blockSize = 0x5A8;
        break;
    case 2:
        blockSize = 0x138;
        break;
    case 3:
        blockSize = 0x194;
        break;
    default:
        blockSize = 0;
        break;
    }
    data_ov021_020b56c0 = (SubModeState *)NNSi_FndGetCurrentRootHeap();
    MIi_CpuClear32(0, &initial, sizeof(initial));
    *data_ov021_020b56c0 = initial;
    data_ov021_020b56c0->heap = heap;
    data_ov021_020b56c0->mode = mode;
    if (blockSize != 0) {
        data_ov021_020b56c0->block = NNSi_FndAllocFromExpHeapEx(blockSize, data_ov021_020b56c0->heap);
        MI_CpuFill8(data_ov021_020b56c0->block, 0, blockSize);
    } else {
        data_ov021_020b56c0->block = NULL;
    }
    func_02029f8c(0, data_ov021_020b52b0[mode]);
    switch (mode) {
    case 0:
        data_ov021_020b56c0->update = func_ov046_020c08c0(arg, data_ov021_020b56c0->block);
        break;
    case 1:
        data_ov021_020b56c0->update = func_ov042_020bdb6c(arg, data_ov021_020b56c0->block);
        break;
    case 2:
        data_ov021_020b56c0->update = InitCameraState_020bcbec(arg, data_ov021_020b56c0->block);
        break;
    case 3:
        data_ov021_020b56c0->update = InitPanel(arg, data_ov021_020b56c0->block);
        break;
    }
}
