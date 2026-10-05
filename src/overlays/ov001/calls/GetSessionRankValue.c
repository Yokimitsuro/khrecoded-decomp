#include "nitro/types.h"

extern int func_ov001_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern s32 func_ov032_020bb828(void);
extern u8 data_ov001_0209e470[5];

static inline s32 GetSessionMode(void)
{
    if (func_ov001_02063a24()) {
        return func_ov001_02063a38();
    }
    return 0;
}

u8 GetSessionRankValue(int kind)
{
    u16 rank = 0;

    if (func_ov001_02063a24()) {
        if (GetSessionMode() == 10 && kind != 99) {
            rank = func_ov032_020bb828();
        }
    }
    if (rank >= 5) {
        rank = 0;
    }
    return data_ov001_0209e470[rank];
}
