#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

typedef struct StatusMenu {
    u8 pad_0000[0x10e0];
    ResourceContainer *container;
    u8 pad_10e4[0x1108 - 0x10e4];
    BOOL pageVisible;
} StatusMenu;

typedef struct StatusPage {
    u8 pad_00[0xb4];
    void *element;
    s16 columnCells[3][7];
} StatusPage;

extern void IndexedRecords_SetFlag2(ResourceContainer *container, int cellIndex, BOOL visible);
extern void SetEntrySlotsVisible(ResourceContainer *container, void *element, BOOL visible);

void HideStatusPageRows(StatusMenu *menu, StatusPage *page)
{
    int row = 0;
    ResourceContainer *container = menu->container;

    do {
        IndexedRecords_SetFlag2(container, page->columnCells[0][row], FALSE);
        IndexedRecords_SetFlag2(container, page->columnCells[1][row], FALSE);
        IndexedRecords_SetFlag2(container, page->columnCells[2][row], FALSE);
        row++;
    } while (row < 7);
    SetEntrySlotsVisible(menu->container, page->element, FALSE);
    menu->pageVisible = FALSE;
}
