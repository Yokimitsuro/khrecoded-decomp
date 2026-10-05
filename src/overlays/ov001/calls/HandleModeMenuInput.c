#include "nitro/types.h"

typedef struct ModeContext {
    u8 pad_00[0xc];
    s32 mode;
    u8 pad_10[0x58];
    s32 canClose;
} ModeContext;

extern ModeContext *data_ov001_020a04e4;
extern u16 data_02060500;

extern void UpdateMessageWindow_0207a68c(int value);
extern void func_ov001_0207a73c(int choice);

void HandleModeMenuInput(void)
{
    ModeContext *context = data_ov001_020a04e4;

    switch (context->mode) {
    case 6:
        if (data_02060500 & 1) {
            UpdateMessageWindow_0207a68c(0);
        } else if (data_02060500 & 0x40) {
            func_ov001_0207a73c(0);
        } else if (data_02060500 & 0x80) {
            if (context->canClose == 0) {
                UpdateMessageWindow_0207a68c(0);
            } else {
                func_ov001_0207a73c(1);
            }
        } else if (data_02060500 & 0x20) {
            func_ov001_0207a73c(2);
        } else if (data_02060500 & 0x10) {
            func_ov001_0207a73c(3);
        }
        break;
    case 5:
        if (data_02060500 & 0x40) {
            UpdateMessageWindow_0207a68c(0);
            func_ov001_0207a73c(0);
        } else if (data_02060500 & 0x80) {
            UpdateMessageWindow_0207a68c(0);
            func_ov001_0207a73c(1);
        } else if (data_02060500 & 0x20) {
            UpdateMessageWindow_0207a68c(0);
            func_ov001_0207a73c(2);
        } else if (data_02060500 & 0x10) {
            UpdateMessageWindow_0207a68c(0);
            func_ov001_0207a73c(3);
        }
        break;
    default:
        if ((data_02060500 & 1) || (data_02060500 & 0x200) || (data_02060500 & 0x100)) {
            UpdateMessageWindow_0207a68c(0);
        }
        break;
    }
}
