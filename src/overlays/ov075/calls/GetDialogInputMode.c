#include "nitro/types.h"

typedef struct {
    s32 state;
    s32 mode;
} DialogWindow;

typedef struct {
    u8 pad_0000[0x8020];
    DialogWindow dialog;
} MatrixMenu;

s32 GetDialogInputMode(MatrixMenu *menu)
{
    if (menu->dialog.state == 4) {
        return 0;
    }
    if (menu->dialog.mode == 2) {
        return 2;
    }
    return 1;
}
