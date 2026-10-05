#include "nitro/types.h"

typedef struct TextWindowEntry {
    u8 data[0x110];
} TextWindowEntry;

typedef struct OverlayWork {
    u8 pad_0000[0x64fc];
    TextWindowEntry windows[3];
} OverlayWork;

extern OverlayWork *gTextWindowResourceTable;
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void MIi_CpuClearFast(int value, void *dst, u32 size);
extern void SetTimerDuration(TextWindowEntry *entry, int state);

void PushTextWindowHistory(void)
{
    MIi_CpuCopyFast(&gTextWindowResourceTable->windows[1], &gTextWindowResourceTable->windows[2], sizeof(TextWindowEntry));
    MIi_CpuCopyFast(&gTextWindowResourceTable->windows[0], &gTextWindowResourceTable->windows[1], sizeof(TextWindowEntry));
    MIi_CpuClearFast(0, &gTextWindowResourceTable->windows[0], sizeof(TextWindowEntry));
    SetTimerDuration(&gTextWindowResourceTable->windows[0], 1);
}
