#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct WidgetPos {
    fx32 x;
    fx32 y;
} WidgetPos;

typedef struct TabMenu {
    u8 pad_000[0x1d0];
    void *cells;
    u8 pad_1d4[0x28];
    int *tabHighlight;
    int *tabCursor;
} TabMenu;

extern WidgetPos *func_ov027_020b91c8(void *cells, int *widget);
extern void func_ov027_020b91e8(void *cells, int *widget, WidgetPos *pos, int mode);
extern void SetEntrySlotsVisible(void *cells, int *slots, int visible);

void MoveTabCursor(TabMenu *menu, int tab)
{
    if (tab == 0) {
        SetEntrySlotsVisible(menu->cells, menu->tabHighlight, 1);
        SetEntrySlotsVisible(menu->cells, menu->tabCursor, 0);
    } else {
        int *cursor = menu->tabCursor;
        WidgetPos pos = *func_ov027_020b91c8(menu->cells, cursor);

        SetEntrySlotsVisible(menu->cells, menu->tabHighlight, 0);
        SetEntrySlotsVisible(menu->cells, cursor, 1);
        pos.x += (tab - 1) << 16;
        func_ov027_020b91e8(menu->cells, cursor, &pos, 1);
    }
}
