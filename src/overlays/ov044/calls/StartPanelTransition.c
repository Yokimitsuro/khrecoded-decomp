#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 words[6];
} PanelTransition;

extern u32 data_ov044_020d0ec0;
extern PanelTransition data_ov044_020d0ea0;

extern void SnapshotPanelPose(void);

void StartPanelTransition(const PanelTransition *transition, const VecFx32 *target, u32 data)
{
    *(u32 *)(data_ov044_020d0ec0 + 0x44) = 6;
    *(u32 *)(data_ov044_020d0ec0 + 0x64) = 0;
    *(u32 *)(data_ov044_020d0ec0 + 0x68) = data;
    *(u32 *)(data_ov044_020d0ec0 + 0x6c) = 1;
    *(VecFx32 *)(data_ov044_020d0ec0 + 0xd0) = *target;
    data_ov044_020d0ea0 = *transition;
    SnapshotPanelPose();
}
