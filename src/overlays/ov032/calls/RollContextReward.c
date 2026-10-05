#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    u16 chances[4];
    u8 pad_1c[0x54];
    u8 rewards[4];
} RewardContext;

extern struct { RewardContext *context; } data_ov032_020c0080;
extern unsigned int func_0202a9e4(unsigned int range);

int RollContextReward(int mode)
{
    int roll;
    int i;

    if (mode == 0) {
        return mode;
    }
    roll = func_0202a9e4(1000);
    if (mode == 1) {
        for (i = 0; i < 3; i++) {
            if (data_ov032_020c0080.context->chances[i] > roll) {
                return data_ov032_020c0080.context->rewards[i];
            }
            roll -= data_ov032_020c0080.context->chances[i];
        }
    } else if (mode == 2) {
        if (data_ov032_020c0080.context->chances[3] > roll) {
            return data_ov032_020c0080.context->rewards[3];
        }
    }
    return 0;
}
