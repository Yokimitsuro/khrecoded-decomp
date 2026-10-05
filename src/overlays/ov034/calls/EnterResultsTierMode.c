#include "nitro/types.h"

typedef struct ResultsParams {
    u8 pad_00[0x8c];
    s32 isBonusStage;
} ResultsParams;

typedef struct ResultsWork {
    u8 pad_0000[0x6bbc];
    s32 tierThresholds[3];
    u8 pad_6bc8[0x30];
    s32 tierIndex;
    u8 pad_6bfc[0x188];
    s32 tierTimer;
} ResultsWork;

typedef struct ResultsScreen {
    ResultsParams *params;
    ResultsWork *work;
} ResultsScreen;

extern ResultsScreen data_ov034_020c0fa0;
extern void SetResultsMode(u32 mode);

void EnterResultsTierMode(u32 mode)
{
    SetResultsMode(mode);
    data_ov034_020c0fa0.work->tierIndex = 0;
    if (data_ov034_020c0fa0.params->isBonusStage != 0) {
        data_ov034_020c0fa0.work->tierThresholds[2] = 100;
        data_ov034_020c0fa0.work->tierThresholds[1] = data_ov034_020c0fa0.work->tierThresholds[2];
        data_ov034_020c0fa0.work->tierThresholds[0] = data_ov034_020c0fa0.work->tierThresholds[1];
    } else {
        data_ov034_020c0fa0.work->tierThresholds[0] = 10;
        data_ov034_020c0fa0.work->tierThresholds[1] = 30;
        data_ov034_020c0fa0.work->tierThresholds[2] = 50;
    }
    data_ov034_020c0fa0.work->tierTimer = 0;
}
