#include "nitro/types.h"

typedef struct ButtonRecord {
    u16 id;
    s16 x;
    s16 y;
} ButtonRecord;

typedef struct SelectMenu {
    u8 selection;
    u8 pad1[0xaf];
    void *records;
    ButtonRecord *buttons[2];
    void *cursor;
} SelectMenu;

extern void func_ov027_020b8514(void *records, void *cursor, int x, int y);
extern void func_ov027_020b847c(void *records, void *cursor);
extern void func_ov027_020b8230(void *pool, void *record);

void RefreshSelectButtons(SelectMenu *menu)
{
    s16 i;

    for (i = 0; i < 2; i++) {
        if (i == menu->selection) {
            func_ov027_020b8514(menu->records, menu->cursor, menu->buttons[i]->x, menu->buttons[i]->y);
            func_ov027_020b847c(menu->records, menu->cursor);
        } else {
            func_ov027_020b8230(menu->records, menu->buttons[i]);
        }
    }
}
