#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

typedef struct ListWidget {
    u8 pad_00[0x70];
    u32 values[3];
    u8 pad_7c[0xc];
    ResourceContainer *container;
    void *upArrow;
    void *downArrow;
    u8 pad_94[0xc];
    BOOL busy;
} ListWidget;

extern void func_ov027_020b95a0(ResourceContainer *container, void *element, BOOL visible);
extern void func_ov073_020c305c(ListWidget *list, int mode, u32 *values);

void SetListWidgetBusy(ListWidget *list, BOOL busy)
{
    BOOL visible;

    list->busy = busy;
    visible = TRUE;
    if (busy != 0) {
        visible = FALSE;
    }
    func_ov027_020b95a0(list->container, list->upArrow, visible);
    func_ov027_020b95a0(list->container, list->downArrow, visible);
    func_ov073_020c305c(list, 0, list->values);
}
