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

extern void *func_ov039_020bc1dc(void);
extern void func_0204f0d4(void *recordArray, int recordIndex);

void ReleaseScreenSprites(ItemScreen *screen)
{
    void *recordArray = func_ov039_020bc1dc();
    int i;

    for (i = 0; i < 12; i++) {
        func_0204f0d4(recordArray, screen->sprites[i].spriteIndex);
        screen->sprites[i].spriteIndex = -1;
    }
}
