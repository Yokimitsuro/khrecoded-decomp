#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScrollList {
    s16 itemCount;
    s16 cursor;
    s16 topIndex;
    u8 scrollOffset;
    u8 pad_07[0xd4 - 0x07];
} ScrollList;

typedef struct StatusMenu {
    s8 page;
    u8 pad_01[2];
    u8 flags;
    u8 pad_04[0x10 - 0x04];
    s16 lastCursor;
    u8 pad_12[2];
    BOOL active;
    u8 pad_18[0xdc0 - 0x18];
    u8 textLayer[0x10f4 - 0xdc0];
    ScrollList list;
    s16 dragIndex;
    s16 dragTarget;
    u8 strings[1];
} StatusMenu;

extern void *func_ov039_020bc1ec(void);
extern void *FindWidgetById(void *container, int id);
extern void func_ov027_020b96c0(void *container, void *element, int frame);
extern void func_ov027_020b91e8(void *container, void *element, fx32 *position, int mode);
extern void CallVirtualHandlerSlot1(void *context, int arg);
extern u16 *func_ov027_020ba2c8(void *table, int index);
extern void *func_ov039_020bc9cc(void);
extern void func_02001620(void *layer, int x, int y, int color, u32 flags, const u16 *text, void *fallbackFont, int maxWidth);
extern void FlushBufferAndRunCallback(void *context);

void ResetStatusPageState(StatusMenu *menu)
{
    void *container = func_ov039_020bc1ec();
    fx32 position[2];
    BOOL active;
    u16 *title;

    position[0] = menu->page << 16;
    func_ov027_020b96c0(container, FindWidgetById(container, 0xb), menu->page);
    func_ov027_020b91e8(container, FindWidgetById(container, 2), position, 4);
    active = TRUE;
    if ((menu->flags & 1) == 0 && (menu->flags != 2 || menu->page == 0)) {
        active = FALSE;
    }
    menu->active = active;
    menu->lastCursor = -1;
    menu->list.cursor = 0;
    menu->list.topIndex = 0;
    menu->list.scrollOffset = 0;
    menu->dragIndex = -1;
    menu->dragTarget = -1;
    if (menu->page != 4) {
        CallVirtualHandlerSlot1(menu->textLayer, 0);
        title = func_ov027_020ba2c8(menu->strings, menu->page + 1);
        func_02001620(menu->textLayer, 0, 5, 2, 8, title, func_ov039_020bc9cc(), 0x4c);
        FlushBufferAndRunCallback(menu->textLayer);
    }
}
