#include "nitro/types.h"

typedef struct ItemListView {
    u8 pad_0000[0x4580];
    u16 visibleCount;
} ItemListView;

extern void func_ov077_020c644c(ItemListView *view, const u32 *categories, u32 categoryCount, BOOL exclude);

u16 BuildItemListForCategories(ItemListView *view, const u32 *categories, u32 categoryCount, BOOL exclude)
{
    func_ov077_020c644c(view, categories, categoryCount, exclude);
    return view->visibleCount;
}
