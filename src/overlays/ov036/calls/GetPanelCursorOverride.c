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

BOOL GetPanelCursorOverride(s32 *outSelection, PanelPoint *outPosition)
{
    PanelOverride *override = &data_ov036_020c3940.work->override;

    if (override->isSet) {
        if (override->selection != -1) {
            *outSelection = override->selection;
        }
        if (override->position.x != -1) {
            *outPosition = override->position;
        }
        return TRUE;
    }
    return FALSE;
}
