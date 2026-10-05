#include "nitro/types.h"

typedef struct ItemList {
    u8 pad_0000[0x4580];
    u16 filteredCount;
} ItemList;

typedef struct MenuPanel {
    u8 pad_00000[0x7f8];
    ItemList list;
    u8 pad_0857A[0x11e24 - 0x7f8 - sizeof(ItemList)];
    u8 customCategoryCount;
    u8 pad_11E25[3];
    u32 customCategories[1];
} MenuPanel;

extern const s8 data_ov076_020cd124[];
extern const u32 data_ov076_020cd22c[];

extern u16 ItemList_FilterByCategory(ItemList *list, u32 category);
extern u16 ItemList_FilterByCategorySet(ItemList *list, const u32 *categories, u32 categoryCount, BOOL invert);

void MenuPanel_ApplyCategoryFilter(MenuPanel *panel, int mode)
{
    int category = data_ov076_020cd124[mode];
    const u32 *categories;
    u32 count;

    if (category < 0) {
        if (category == -1) {
            categories = panel->customCategories;
            count = panel->customCategoryCount;
        } else {
            categories = data_ov076_020cd22c;
            count = 3;
        }
        ItemList_FilterByCategorySet(&panel->list, categories, count, FALSE);
        return;
    }
    ItemList_FilterByCategory(&panel->list, category);
}
