typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;
typedef u32 NNSGfdTexKey;

typedef struct NNSGfdFrmTexVramManager {
    u16 numSlots;
} NNSGfdFrmTexVramManager;

extern NNSGfdFrmTexVramManager sFrmTexVramManager;
extern NNSGfdTexKey (*sDefaultAllocTexVramFunc)(u32, BOOL, u32);
extern int (*sDefaultFreeTexVramFunc)(NNSGfdTexKey);

extern void GfdFrmTexVram_SetRegionOrder_(int, int, int, int, int);
extern void NNS_GfdResetFrmTexVramState(void);
extern NNSGfdTexKey NNS_GfdAllocFrmTexVram(u32 size, BOOL compressed, u32 option);
extern int NNS_GfdFreeFrmTexVram(NNSGfdTexKey key);

void NNS_GfdInitFrmTexVramManager(u16 numSlots, BOOL useAsDefault)
{
    if (numSlots <= 2) {
        GfdFrmTexVram_SetRegionOrder_(4, 3, 2, 0, 1);
    } else {
        GfdFrmTexVram_SetRegionOrder_(4, 3, 0, 2, 1);
    }

    sFrmTexVramManager.numSlots = numSlots;
    NNS_GfdResetFrmTexVramState();

    if (useAsDefault) {
        sDefaultAllocTexVramFunc = NNS_GfdAllocFrmTexVram;
        sDefaultFreeTexVramFunc = NNS_GfdFreeFrmTexVram;
    }
}
