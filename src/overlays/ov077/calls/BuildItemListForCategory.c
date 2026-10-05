#include "nitro/types.h"

typedef struct ItemListView {
    u8 pad_0000[0x4580];
    u16 visibleCount;
} ItemListView;

extern void BuildItemListForType(ItemListView *view, u32 category);

u16 BuildItemListForCategory(ItemListView *view, u32 category)
{
    BuildItemListForType(view, category);
    return view->visibleCount;
}
