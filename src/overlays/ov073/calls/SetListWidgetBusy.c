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

extern void SetEntrySlotsVisible(ResourceContainer *container, void *element, BOOL visible);
extern void RefreshListRowStates(ListWidget *list, int mode, u32 *values);

void SetListWidgetBusy(ListWidget *list, BOOL busy)
{
    BOOL visible;

    list->busy = busy;
    visible = TRUE;
    if (busy != 0) {
        visible = FALSE;
    }
    SetEntrySlotsVisible(list->container, list->upArrow, visible);
    SetEntrySlotsVisible(list->container, list->downArrow, visible);
    RefreshListRowStates(list, 0, list->values);
}
