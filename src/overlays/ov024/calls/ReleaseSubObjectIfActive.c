#include "nitro/types.h"

extern u32 data_ov024_020b7540;
extern void UpdateWidgetRootAndFireAlarm(u32 target, u32 mode);

void ReleaseSubObjectIfActive(void) {
    if (*(int *)(data_ov024_020b7540 + 0x64f4) != 0) {
        UpdateWidgetRootAndFireAlarm(data_ov024_020b7540 + 0x74, 0);
        *(u32 *)(data_ov024_020b7540 + 0x64f4) = 0;
    }
}
