#include "nitro/types.h"

typedef struct Panel Panel;

typedef struct {
    void (*enter)(Panel *panel);
    void (*update)(Panel *panel);
    void (*exit)(Panel *panel);
} PanelPhaseHandlers;

struct Panel {
    u8 pad_00[0x2c];
    s32 phase;
    u8 pad_30[4];
    u32 phaseArg;
    u8 pad_38[4];
    u32 elapsed;
};

extern PanelPhaseHandlers gPanelPhaseHandlers[];
extern void func_ov000_02061b88(int brightness, int waitVBlank);

void EnterPanelPhase(Panel *panel, s32 phase, u32 phaseArg, int brightness)
{
    panel->phase = phase;
    panel->phaseArg = phaseArg;
    panel->elapsed = 0;
    func_ov000_02061b88(brightness, 1);
    gPanelPhaseHandlers[phase].enter(panel);
}
