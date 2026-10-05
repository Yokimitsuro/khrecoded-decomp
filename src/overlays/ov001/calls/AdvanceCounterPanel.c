#include "nitro/types.h"

typedef struct CounterPanel {
    u8 current;
    u8 total;
    u8 pad_02[0xa];
    u32 timerStart;
    u8 pad_10[8];
    u32 startTick;
    u8 pad_1c[4];
    u16 history[2];
    u16 state;
    u16 pending : 14;
    u16 pendingHigh : 2;
    u32 flags;
    u32 historyIndex;
    u8 pad_30[0x10];
    u32 finishGraphics;
    u32 stepGraphics;
} CounterPanel;

extern char data_ov001_0209dff0[];
extern void func_ov001_0207123c(void);
extern u16 RefreshCounterRecordPositions(CounterPanel *panel);
extern u16 func_ov001_0207d860(u32 value);
extern void func_ov001_0207d828(CounterPanel *panel, u32 graphics);
extern void ShowTwoDigitCounters(CounterPanel *panel);
extern void NNS_GfdRegisterNewVramTransferTask(u32 a, u32 b, u32 c, u32 d);
extern u32 func_0202a7b8(void);

BOOL AdvanceCounterPanel(CounterPanel *panel)
{
    BOOL finished;
    u32 value;

    func_ov001_0207123c();
    finished = FALSE;
    if (panel->current < panel->total) {
        panel->current++;
    }
    value = panel->pending;
    if (value >= 1 && value <= 3) {
        value = RefreshCounterRecordPositions(panel);
    }
    panel->history[panel->historyIndex] = func_ov001_0207d860(value);
    panel->historyIndex ^= 1;
    NNS_GfdRegisterNewVramTransferTask(0xf, 0x1c2, (u32)data_ov001_0209dff0, 0xe);
    panel->state = 1;
    panel->pending = 0;
    panel->flags &= ~2;
    if (panel->current == panel->total) {
        func_ov001_0207d828(panel, panel->finishGraphics);
        panel->timerStart = 0;
        panel->startTick = func_0202a7b8();
        finished = TRUE;
    } else {
        func_ov001_0207d828(panel, panel->stepGraphics);
    }
    ShowTwoDigitCounters(panel);
    return finished;
}
