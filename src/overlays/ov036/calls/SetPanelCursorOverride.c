#include "nitro/types.h"

typedef struct PanelPoint {
    s32 x;
    s32 y;
} PanelPoint;

typedef struct PanelOverride {
    PanelPoint position;
    s32 selection;
    BOOL isSet;
} PanelOverride;

typedef struct PanelWork {
    u8 pad_0000[0x10ec];
    PanelOverride override;
} PanelWork;

typedef struct PanelContext {
    u32 unk_00;
    PanelWork *work;
} PanelContext;

extern PanelContext data_ov036_020c3940;

void SetPanelCursorOverride(s32 selection, PanelPoint *position)
{
    PanelOverride *override = &data_ov036_020c3940.work->override;

    override->selection = selection;
    override->position = *position;
    override->isSet = TRUE;
}
