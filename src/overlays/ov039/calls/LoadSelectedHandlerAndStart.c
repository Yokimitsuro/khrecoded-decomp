#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xc998];
    int handlerEvent;
    void *handlerWork;
    u8 pad_c9a0[0x20];
    int handlerParam;
    u8 pad_c9c4[0x6c];
    int handlerReady;
} Ov039State;

extern Ov039State *data_ov039_020bea20;
extern void func_ov039_020bcf40(int event);
extern void LoadSecondarySubOverlay(int param);
extern u32 func_ov039_020bd694(void);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern int func_ov039_020bcfec(int event);
extern void RuntimeState_SetMode(int value);
extern void InitStreamBufferPair(int blockCount, u32 flag);

void LoadSelectedHandlerAndStart(void)
{
    Ov039State *state = data_ov039_020bea20;

    func_ov039_020bcf40(state->handlerEvent);
    if (state->handlerWork == NULL) {
        u32 size;
        LoadSecondarySubOverlay(state->handlerParam);
        size = func_ov039_020bd694();
        state->handlerWork = NNSi_FndAllocFromDefaultHeap(size);
        MI_CpuFill8(state->handlerWork, 0, size);
    }
    if (state->handlerReady == 0) {
        state->handlerReady = func_ov039_020bcfec((int)state->handlerWork);
    }
    if (state->handlerReady == 0) {
        return;
    }
    RuntimeState_SetMode(6);
    InitStreamBufferPair(0, 100);
}
