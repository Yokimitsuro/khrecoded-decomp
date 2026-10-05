#include "nitro/types.h"

typedef struct ScreenSprite {
    s32 x;
    s32 y;
    s32 unk_08;
    s32 animIndex;
    s32 unk_10;
    s32 spriteIndex;
} ScreenSprite;

typedef struct ItemScreen {
    u8 pad_00000[0x11ed4];
    ScreenSprite sprites[12];
    s32 state;
} ItemScreen;

void InitScreenSpriteSlots(ItemScreen *screen)
{
    screen->sprites[0].x = 0xc4;
    screen->sprites[0].y = 0x34;
    screen->sprites[0].unk_08 = 0;
    screen->sprites[0].animIndex = 0x1e;
    screen->sprites[0].unk_10 = -1;
    screen->sprites[0].spriteIndex = -1;
    screen->sprites[1].x = 0xc8;
    screen->sprites[1].y = 0x34;
    screen->sprites[1].unk_08 = 0;
    screen->sprites[1].animIndex = 0x1e;
    screen->sprites[1].unk_10 = -1;
    screen->sprites[1].spriteIndex = -1;
    screen->sprites[2].x = 0xcc;
    screen->sprites[2].y = 0x34;
    screen->sprites[2].unk_08 = 0;
    screen->sprites[2].animIndex = 0x1e;
    screen->sprites[2].unk_10 = -1;
    screen->sprites[2].spriteIndex = -1;
    screen->sprites[3].x = 0xd0;
    screen->sprites[3].y = 0x34;
    screen->sprites[3].unk_08 = 0;
    screen->sprites[3].animIndex = 0x1e;
    screen->sprites[3].unk_10 = -1;
    screen->sprites[3].spriteIndex = -1;
    screen->sprites[4].x = 0xc2;
    screen->sprites[4].y = 0x2e;
    screen->sprites[4].unk_08 = 0;
    screen->sprites[4].animIndex = 0x1d;
    screen->sprites[4].unk_10 = -1;
    screen->sprites[4].spriteIndex = -1;
    screen->sprites[5].x = 0xc2;
    screen->sprites[5].y = 0x2e;
    screen->sprites[5].unk_08 = 0;
    screen->sprites[5].animIndex = 0x1c;
    screen->sprites[5].unk_10 = -1;
    screen->sprites[5].spriteIndex = -1;
    screen->sprites[6].x = 0xcc;
    screen->sprites[6].y = 0x31;
    screen->sprites[6].unk_08 = 0;
    screen->sprites[6].animIndex = 0x20;
    screen->sprites[6].unk_10 = -1;
    screen->sprites[6].spriteIndex = -1;
    screen->sprites[7].x = 0;
    screen->sprites[7].y = 0;
    screen->sprites[7].unk_08 = 0;
    screen->sprites[7].animIndex = 0;
    screen->sprites[7].unk_10 = -1;
    screen->sprites[7].spriteIndex = -1;
    screen->sprites[8].x = 0;
    screen->sprites[8].y = 0;
    screen->sprites[8].unk_08 = 0;
    screen->sprites[8].animIndex = 0x7;
    screen->sprites[8].unk_10 = -1;
    screen->sprites[8].spriteIndex = -1;
    screen->sprites[9].x = 0;
    screen->sprites[9].y = 0;
    screen->sprites[9].unk_08 = 0;
    screen->sprites[9].animIndex = 0x8;
    screen->sprites[9].unk_10 = -1;
    screen->sprites[9].spriteIndex = -1;
    screen->sprites[10].x = 0;
    screen->sprites[10].y = 0;
    screen->sprites[10].unk_08 = 0;
    screen->sprites[10].animIndex = 0x5;
    screen->sprites[10].unk_10 = -1;
    screen->sprites[10].spriteIndex = -1;
    screen->sprites[11].x = 0;
    screen->sprites[11].y = 0;
    screen->sprites[11].unk_08 = 0;
    screen->sprites[11].animIndex = 0x6;
    screen->sprites[11].unk_10 = -1;
    screen->sprites[11].spriteIndex = -1;
}
