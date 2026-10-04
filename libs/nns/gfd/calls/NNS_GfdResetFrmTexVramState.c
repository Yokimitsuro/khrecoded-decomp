typedef unsigned int u32;
typedef unsigned short u16;
typedef int BOOL;

typedef struct NNSGfdFrmTexVramManager {
    u16 numSlots;
} NNSGfdFrmTexVramManager;

typedef struct NNSGfdFrmTexRegionState {
    u32 head;
    u32 tail;
    BOOL active;
    const BOOL halfSize;
    const u16 index;
    const u16 padding;
    const u32 baseAddress;
} NNSGfdFrmTexRegionState;

extern NNSGfdFrmTexVramManager sFrmTexVramManager;
extern NNSGfdFrmTexRegionState sFrmTexVramRegions[5];

static inline void ResetNormalRegion(NNSGfdFrmTexRegionState *region)
{
    region->head = 0;
    region->tail = 0x20000;
}

static inline void ResetHalfRegion(NNSGfdFrmTexRegionState *region)
{
    region->head = 0;
    region->tail = 0x10000;
}

void NNS_GfdResetFrmTexVramState(void)
{
    int i;
    u16 numSlots = sFrmTexVramManager.numSlots;
    const int numRegions = numSlots > 1 ? numSlots + 1 : numSlots;

    for (i = 0; i < 5; i++) {
        if (i < numRegions) {
            sFrmTexVramRegions[i].active = 1;
        } else {
            sFrmTexVramRegions[i].active = 0;
        }

        if (sFrmTexVramRegions[i].halfSize) {
            ResetHalfRegion(&sFrmTexVramRegions[i]);
        } else {
            ResetNormalRegion(&sFrmTexVramRegions[i]);
        }
    }
}