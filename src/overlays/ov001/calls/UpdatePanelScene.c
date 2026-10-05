#include "nitro/types.h"

typedef struct PanelScene PanelScene;
typedef void (*PanelStateFn)(PanelScene *panel);

typedef struct PanelStateTable {
    PanelStateFn handlers[7];
} PanelStateTable;

struct PanelScene {
    u8 pad_000[0x30];
    int state;
    u8 pad_034[0xc];
    int touchActive;
    u8 pad_044[0x102 - 0x44];
    u8 channel;
    u8 pad_103[5];
    int timerMode;
};

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchSample;

extern PanelScene *data_ov001_020a04e8;
extern PanelStateTable gMenuOverlayStateHandlers;
extern u8 GetPrimarySelectionByte1E(void);
extern BOOL func_ov001_020645c8(u32 value);
extern int func_ov001_02064784(void);
extern void func_ov001_0207a9f4(PanelScene *panel);
extern void UpdateIdleTimerToggle(PanelScene *panel);
extern void func_ov001_0207af6c(PanelScene *panel);
extern u32 func_ov001_0207b3f4(void);
extern BOOL func_ov001_0207b610(void);
extern void ClearPanelInputActive(void);
extern int LookupChannelEntry_020b62ac(int channel);
extern int func_ov027_020b9f9c(TouchSample *sample);
extern void ClearCapturedTouchState(void);

int UpdatePanelScene(void)
{
    PanelScene *panel = data_ov001_020a04e8;
    TouchSample sample;
    PanelStateTable table = gMenuOverlayStateHandlers;
    u8 channel = GetPrimarySelectionByte1E();

    if (table.handlers[panel->state] != NULL) {
        table.handlers[panel->state](panel);
    }
    if (panel->channel != channel && func_ov001_0207b3f4() == 2 && func_ov001_0207b610()) {
        LookupChannelEntry_020b62ac(channel);
        panel->channel = channel;
    }
    if (!func_ov001_02064784() && func_ov001_020645c8(0x370b)) {
        func_ov001_0207af6c(panel);
    } else {
        switch (panel->timerMode) {
        case 0:
            UpdateIdleTimerToggle(panel);
            break;
        case 1:
            func_ov001_0207af6c(panel);
            break;
        case 2:
            break;
        }
    }
    if (func_ov001_0207b3f4() == 0 && func_ov001_0207b610()) {
        func_ov001_0207a9f4(panel);
    }
    if (panel->touchActive != 0) {
        func_ov027_020b9f9c(&sample);
        if (sample.touch == 0) {
            ClearPanelInputActive();
        } else {
            ClearCapturedTouchState();
        }
    }
    return 0;
}
