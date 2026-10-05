#include "nitro/types.h"

typedef struct ListMenu {
    int mode;
    u8 pad4[0x1c];
    int active;
    u8 pad24[0x88];
    int cursor;
    int itemCount;
} ListMenu;

extern ListMenu *data_ov001_020a04f4;
extern int HandleFallingPieceInput(ListMenu *menu, u32 keys);
extern int HandleDirectionalPrompt(ListMenu *menu, u32 keys);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

int HandleListMenuConfirm(u32 keys) {
    ListMenu *menu = data_ov001_020a04f4;
    int result = 5;

    keys &= 0xc03;
    if (keys == 0 || menu->active == 0 || menu->cursor >= menu->itemCount) {
        return 5;
    }
    switch (menu->mode) {
    case 1:
        result = HandleFallingPieceInput(menu, keys);
        break;
    case 2:
    case 3:
        result = HandleDirectionalPrompt(menu, keys);
        break;
    }
    if (result != 5 && result != 4) {
        PlaySoundEffect(0, 0x42);
    }
    return result;
}
