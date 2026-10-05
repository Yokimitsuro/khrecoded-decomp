#include "nitro/types.h"

typedef struct {
    u8 pad000[0x140];
    int scroll;
    int pad144;
    int repeatTicks;
    int holdDelay;
} RecordPanel;

extern u16 data_02060500;
extern u16 data_020604fc;
extern void func_ov086_020c14e0(RecordPanel *panel, int scroll);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void HandleRecordScrollInput(RecordPanel *panel)
{
    int scroll = panel->scroll;
    BOOL resetDelay = TRUE;
    int target;

    if (scroll == 0 && (data_02060500 & 0x40)) {
        func_ov086_020c14e0(panel, 0x38);
        PlaySoundEffect(0, 0);
        panel->holdDelay = 1;
        resetDelay = FALSE;
        panel->repeatTicks = -1;
    } else if (scroll == 0x38 && (data_02060500 & 0x80)) {
        func_ov086_020c14e0(panel, 0);
        PlaySoundEffect(0, 0);
        panel->holdDelay = 1;
        resetDelay = FALSE;
        panel->repeatTicks = -1;
    } else if (data_020604fc & 0x40) {
        if (panel->holdDelay > 0) {
            panel->holdDelay++;
            if (panel->holdDelay >= 12) {
                panel->holdDelay = 0;
            }
            resetDelay = FALSE;
        } else {
            panel->repeatTicks++;
            target = panel->scroll - 2;
            if (target > 0x38) {
                target = 0x38;
            } else if (target < 0) {
                target = 0;
            }
            func_ov086_020c14e0(panel, target);
        }
    } else if (data_020604fc & 0x80) {
        if (panel->holdDelay > 0) {
            panel->holdDelay++;
            if (panel->holdDelay >= 12) {
                panel->holdDelay = 0;
            }
            resetDelay = FALSE;
        } else {
            panel->repeatTicks++;
            target = panel->scroll + 2;
            if (target > 0x38) {
                target = 0x38;
            } else if (target < 0) {
                target = 0;
            }
            func_ov086_020c14e0(panel, target);
        }
    } else if (data_02060500 & 0x20) {
        if (scroll > 0) {
            target = scroll - 0x23;
            if (target > 0x38) {
                target = 0x38;
            } else if (target < 0) {
                target = 0;
            }
            func_ov086_020c14e0(panel, target);
            PlaySoundEffect(0, 0);
            panel->repeatTicks = -1;
        }
    } else if (data_02060500 & 0x10) {
        if (scroll < 0x38) {
            target = scroll + 0x23;
            if (target > 0x38) {
                target = 0x38;
            } else if (target < 0) {
                target = 0;
            }
            func_ov086_020c14e0(panel, target);
            PlaySoundEffect(0, 0);
            panel->repeatTicks = -1;
        }
    } else {
        panel->repeatTicks = -1;
    }
    if (panel->repeatTicks >= 0) {
        panel->repeatTicks %= 4;
        if (panel->repeatTicks == 0) {
            PlaySoundEffect(0, 0);
        }
    }
    if (resetDelay) {
        panel->holdDelay = 0;
    }
}
