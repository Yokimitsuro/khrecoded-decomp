#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x667c];
    int number;
    BOOL useAltMode;
    BOOL requestSent;
    u8 pad_6688[0x66a4 - 0x6688];
    BOOL (*isRequestDone)(void);
} Panel;

extern BOOL IsSoundStreamActive(int handleIndex);
extern void SetPanelState(Panel *panel, s32 state, u32 param1, u32 param2);
extern void SubmitNumberedPanelRequest(Panel *panel, BOOL useAltMode, int number);

s32 UpdatePanelRequest(Panel *panel)
{
    s32 result = -1;

    if (panel->requestSent) {
        if (panel->isRequestDone()) {
            if (panel->useAltMode) {
                SetPanelState(panel, 1, 0, 0);
                result = 10;
            } else {
                SetPanelState(panel, 1, 0, 0x10);
                result = 6;
            }
        }
    } else if (!IsSoundStreamActive(0)) {
        SubmitNumberedPanelRequest(panel, panel->useAltMode, panel->number);
        panel->requestSent = TRUE;
    }
    return result;
}
