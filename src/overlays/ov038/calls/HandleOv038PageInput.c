#include "nitro/types.h"

typedef struct Ov038Context {
    u8 pad_0000[0xd0ac];
    s32 page;
} Ov038Context;

extern Ov038Context *data_ov038_020bd164;
extern u16 data_02060500;
extern void PlaySoundEffect(int player, int sound);
extern void ResetOv038ExitState(int state);
extern void SetOv038SpriteOffset(s32 poolIndex, s32 spriteIndex, s32 offsetX, s32 offsetY);

s32 HandleOv038PageInput(void)
{
    Ov038Context *ctx = data_ov038_020bd164;
    s32 index;

    switch (data_02060500 & 0x301) {
    case 1:
        PlaySoundEffect(0, 1);
        ResetOv038ExitState(3);
        break;
    case 0x100:
    case 0x200:
        ctx->page = (ctx->page + 1) % 2;
        switch (ctx->page) {
        case 0:
            *(vu32 *)0x04001010 = 0;
            for (index = 0; index < 99; index++) {
                if (index != 0x38) {
                    SetOv038SpriteOffset(1, index, 0, 0);
                }
            }
            break;
        case 1:
            *(vu32 *)0x04001010 = 0x100;
            for (index = 0; index < 99; index++) {
                if (index != 0x38) {
                    SetOv038SpriteOffset(1, index, -0x100, 0);
                }
            }
            break;
        }
        PlaySoundEffect(0, 2);
        break;
    }
    return 0;
}
