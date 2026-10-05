#include "nitro/types.h"

typedef struct MenuEntry {
    u8 pad_00[0x10];
    int widgetId;
} MenuEntry;

extern u8 *data_ov025_020b7780;
extern void *func_ov001_0207123c(void);
extern void func_ov027_020b9a94(void *widget, MenuEntry *entry);

void DrawMenuEntryWidget(MenuEntry *entry) {
    switch (entry->widgetId) {
    case 0x1a:
    case 0x1b:
        func_ov027_020b9a94(data_ov025_020b7780 + 0x64c8, entry);
        break;
    default:
        func_ov027_020b9a94(func_ov001_0207123c(), entry);
        break;
    }
}
