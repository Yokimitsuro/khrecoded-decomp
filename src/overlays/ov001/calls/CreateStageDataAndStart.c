#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    s8 selected;
    u8 pad_07[0x138 - 7];
} StageData;

typedef struct {
    u16 stageId;
} StageStartParams;

extern StageData *data_ov001_020a0490;
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClearFast(u32 value, void *dst, u32 size);
extern void StageEvents_StartIfIdle(void *userData);
extern int AcquireRecordSlot(int slot, int param);

void CreateStageDataAndStart(u16 stageId) {
    StageStartParams params;
    data_ov001_020a0490 = NNSi_FndAllocFromDefaultHeap(sizeof(StageData));
    MIi_CpuClearFast(0, data_ov001_020a0490, sizeof(StageData));
    data_ov001_020a0490->selected = -1;
    params.stageId = stageId;
    StageEvents_StartIfIdle(&params);
    AcquireRecordSlot(4, 0);
}
