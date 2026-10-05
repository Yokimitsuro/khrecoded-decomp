#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 GetDifficultyScale(void);
extern int func_ov001_02064574(int bitOffset, u32 bitCount);
extern u32 func_ov001_020664f0(u32 kind, u32 size, u32 arg3, u32 arg4);

void SpawnRewardOrbs(u16 *amounts, u32 arg3, u32 arg4) {
    int i;

    for (i = 0; i < 6; i++) {
        u16 amount = amounts[i];
        u32 kind = i;
        u32 size;

        if (kind != 5 && kind != 2 && kind != 4) {
            amount = (u16)((amount * GetDifficultyScale()) >> 12);
        }
        if (i == 5 && amount != 0) {
            int have = func_ov001_02064574(0x3700, 0x10);
            if ((func_ov001_02064574(0x3710, 3) + 1) * 20 <= have) {
                kind = 0;
            }
        }
        while (amount != 0) {
            if (amount >= 100) {
                size = 2;
                amount -= 100;
            } else if (amount >= 10) {
                size = 1;
                amount -= 10;
            } else {
                size = 0;
                amount--;
            }
            func_ov001_020664f0(kind, size, arg3, arg4);
        }
    }
}
