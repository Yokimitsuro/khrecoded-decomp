#include "nitro/types.h"

typedef struct {
    u8 data[0x28];
} StageLink;

typedef struct {
    u8 data[0x1c8];
} StageEvent;

typedef struct {
    u8 pad_00000[0x208];
    StageLink *links;
    u32 *linkFlags;
    StageEvent *events;
    u8 pad_00214[0x17a14 - 0x214];
    u8 bufferA[0x800];
    u8 bufferB[0x600];
    u8 bufferC[0x280];
    u8 pad_18a94[0x18d7c - 0x18a94];
    void *eventPool;
    u8 pad_18d80[0x18];
    void *controllerPool;
    void *objectPool;
    u8 pad_18da0[0x44];
    u16 eventCount;
    u16 linkCount;
    u16 activeLinks;
    u8 pad_18dea[4];
    u16 pendingA;
    u8 pad_18df0[2];
    u16 pendingB;
    u8 pad_18df4[0x68];
    u32 pendingFlags;
} StageManager;

extern StageManager *data_ov001_020a0528;
extern void HandlePool_ReleaseAll(void *pool);
extern void MI_CpuFill8(void *dst, int value, u32 size);

void ClearStageTables(void)
{
    HandlePool_ReleaseAll(data_ov001_020a0528->eventPool);
    HandlePool_ReleaseAll(data_ov001_020a0528->controllerPool);
    HandlePool_ReleaseAll(data_ov001_020a0528->objectPool);
    MI_CpuFill8(data_ov001_020a0528->events, 0, data_ov001_020a0528->eventCount * sizeof(StageEvent));
    MI_CpuFill8(data_ov001_020a0528->bufferA, 0, sizeof(data_ov001_020a0528->bufferA));
    MI_CpuFill8(data_ov001_020a0528->bufferB, 0, sizeof(data_ov001_020a0528->bufferB));
    MI_CpuFill8(data_ov001_020a0528->bufferC, 0, sizeof(data_ov001_020a0528->bufferC));
    if (data_ov001_020a0528->linkFlags != 0) {
        MI_CpuFill8(data_ov001_020a0528->linkFlags, 0, data_ov001_020a0528->linkCount * sizeof(u32));
    }
    if (data_ov001_020a0528->links != 0) {
        MI_CpuFill8(data_ov001_020a0528->links, 0, data_ov001_020a0528->linkCount * sizeof(StageLink));
    }
    data_ov001_020a0528->pendingA = 0;
    data_ov001_020a0528->pendingB = 0;
    data_ov001_020a0528->activeLinks = 0;
    data_ov001_020a0528->pendingFlags = 0;
}
