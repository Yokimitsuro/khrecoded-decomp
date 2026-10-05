#include "nitro/types.h"

typedef struct DialogRect {
    int left;
    int top;
    int right;
    int bottom;
} DialogRect;

typedef struct MatrixMenu {
    u8 pad_00000[0x13678];
    u8 previewBuffer[1];
} MatrixMenu;

extern const DialogRect data_ov075_020d14e0;
extern int func_ov075_020cbf5c(MatrixMenu *menu, DialogRect *rect, int *args, u8 *message);
extern int *func_01ffb2f8(void *dest, int value, int size);

int OpenPreviewDialog(MatrixMenu *menu, u8 *message, int mode, ...)
{
    int result = 0;

    if (mode == 0) {
        DialogRect rect = data_ov075_020d14e0;
        result = func_ov075_020cbf5c(menu, &rect, &mode, message);
    }
    if (mode != 0) {
        func_01ffb2f8(menu->previewBuffer, 0, *message << 12);
    }
    return result;
}