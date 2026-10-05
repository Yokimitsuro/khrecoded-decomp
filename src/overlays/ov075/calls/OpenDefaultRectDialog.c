#include "nitro/types.h"

typedef struct DialogRect {
    int left;
    int top;
    int right;
    int bottom;
} DialogRect;

extern const DialogRect data_ov075_020d1500;
extern int func_ov075_020cbf5c(void *menu, DialogRect *rect, int *args, int messageId);

int OpenDefaultRectDialog(void *menu, int messageId, int mode, ...)
{
    int result = 0;

    if (mode == 0) {
        DialogRect rect = data_ov075_020d1500;
        result = func_ov075_020cbf5c(menu, &rect, &mode, messageId);
    }
    return result;
}