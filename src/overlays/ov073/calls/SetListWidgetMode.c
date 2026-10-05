#include "nitro/types.h"

typedef struct ListWidget {
    void (*onChange)(void);
    u8 pad_04[0x6c];
    u32 values[3];
    u8 mode;
} ListWidget;

extern void func_ov073_020c305c(ListWidget *list, int mode, u32 *values);

void SetListWidgetMode(ListWidget *list, u8 mode)
{
    u32 values[3] = {0, 0, 0};
    int i;

    list->mode = mode;
    for (i = 0; i < 3; i++) {
        values[i] = list->values[i];
    }
    func_ov073_020c305c(list, 0, values);
    if (list->onChange != NULL) {
        list->onChange();
    }
}
