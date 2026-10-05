#include "nitro/types.h"

typedef struct {
    u8 data[0x2c];
} PopupEntry;

typedef struct {
    u8 pad_0000[0xeea8];
    PopupEntry popups[(0xf060 - 0xeea8) / 0x2c];
    int popupCount;
} MenuScene;

extern int func_ov097_020c188c(PopupEntry *entry);

void ReleasePopupEntries(MenuScene *scene)
{
    int i;

    for (i = 0; i < scene->popupCount; i++) {
        func_ov097_020c188c(&scene->popups[i]);
    }
    scene->popupCount = 0;
}
