#include "nitro/types.h"

extern int data_ov001_0209f2e8;
extern void ResetStageGroupObjects(u16 id);

void CallIfSessionActive(int id)
{
    if (data_ov001_0209f2e8 != -1) {
        ResetStageGroupObjects(id);
    }
}
