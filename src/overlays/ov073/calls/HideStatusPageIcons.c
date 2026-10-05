#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

typedef struct StatusMenu {
    u8 pad_0000[0x14];
    BOOL busy;
    u8 pad_0018[0x10e0 - 0x18];
    ResourceContainer *container;
} StatusMenu;

typedef struct StatusPage {
    u8 pad_000[0x110];
    s16 iconCells[6];
} StatusPage;

extern void SetStatusElementVisible(int elementId, BOOL visible);
extern void IndexedRecords_SetFlag2(ResourceContainer *container, int cellIndex, BOOL visible);
extern void ShowSelectedRecordName(StatusMenu *menu);

void HideStatusPageIcons(StatusMenu *menu, StatusPage *page)
{
    int i = 0;

    SetStatusElementVisible(0xc, FALSE);
    do {
        IndexedRecords_SetFlag2(menu->container, page->iconCells[i], FALSE);
        i++;
    } while (i < 6);
    if (menu->busy == 0) {
        ShowSelectedRecordName(menu);
    }
}
