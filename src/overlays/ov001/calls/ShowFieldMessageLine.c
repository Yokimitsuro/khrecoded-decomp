#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x480];
    u32 isSliding : 1;
    u32 unk_480_1 : 3;
    u32 isPaused : 1;
} FieldManager;

typedef struct {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

extern void func_ov001_02075008(u16 tickerMode, u32 tickerValue);
extern void func_ov001_0206ff10(int messageId);

void ShowFieldMessageLine(u16 tickerMode, u32 tickerValue, int messageId, BOOL resetTicker)
{
    if (data_ov001_020a04c4.manager->isPaused != 1 && tickerValue != 0) {
        if (resetTicker) {
            func_ov001_02075008(tickerMode, tickerValue);
        }
        func_ov001_0206ff10(messageId);
    }
}
