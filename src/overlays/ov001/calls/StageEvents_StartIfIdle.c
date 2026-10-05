#include "nitro/types.h"

extern int data_ov001_0209f2e8;
extern BOOL CreateStageManagerTask(void *userData);

void StageEvents_StartIfIdle(void *userData)
{
    if (data_ov001_0209f2e8 == -1) {
        data_ov001_0209f2e8 = 0;
        CreateStageManagerTask(userData);
    }
}
