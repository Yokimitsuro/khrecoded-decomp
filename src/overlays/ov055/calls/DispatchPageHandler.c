#include "nitro/types.h"

typedef struct MenuPage {
    u8 pad_00[4];
    int kind;
} MenuPage;

extern int SpawnPairedEntryUnit(MenuPage *page, int arg1, int arg2);
extern int SpawnSlotTrackerUnit(MenuPage *page, int arg1, int arg2);

int DispatchPageHandler(MenuPage *page, int arg1, int arg2)
{
    int result = 0;
    switch (page->kind) {
    case 0:
        result = SpawnPairedEntryUnit(page, arg1, arg2);
        break;
    case 4:
        result = SpawnSlotTrackerUnit(page, arg1, arg2);
        break;
    }
    return result;
}
