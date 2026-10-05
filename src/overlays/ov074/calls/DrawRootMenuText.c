#include "nitro/types.h"

typedef struct TextWindow {
    u8 data[0x34];
} TextWindow;

typedef struct MenuEntry {
    u16 *label;
    u16 *description;
    int id;
} MenuEntry;

typedef struct RootMenu {
    u8 cursor;
    u8 entryCount;
    u8 state;
    u8 mode;
    u8 pad_04[0x12 - 0x04];
    u16 unlockMessage;
    u8 pad_14[0x438 - 0x14];
    TextWindow windows[4];
    MenuEntry entries[8];
    u16 *extraLabels[4];
    u8 pad_578[0x5dc - 0x578];
    u8 strings[0xc];
} RootMenu;

extern void CallVirtualHandlerSlot1(TextWindow *window, int arg);
extern int func_ov039_020bc9cc(void);
extern void func_02001620(TextWindow *window, u32 x, u32 y, u32 color, u32 flags, u16 *text, int override, int width);
extern void DrawTextAnchored(TextWindow *window, int x, int y, int color, u32 flags, const u16 *text);
extern void DrawTextColored(TextWindow *window, int x, int y, int color, int altColor, const u16 *text);
extern void DrawTextPackedColor(TextWindow *window, int x, int y, int color, int flags, int highColor, const u16 *text);
extern u16 *func_ov027_020ba2c8(void *table, int index);
extern void Text_UploadTileBuffer(TextWindow *window);

void DrawRootMenuText(RootMenu *menu)
{
    s16 i = 0;

    CallVirtualHandlerSlot1(&menu->windows[1], 0);
    CallVirtualHandlerSlot1(&menu->windows[2], 0);
    CallVirtualHandlerSlot1(&menu->windows[3], 0);
    if (menu->mode == 0) {
        for (; i < menu->entryCount; i++) {
            func_02001620(&menu->windows[1], (i == menu->cursor) ? 8 : 0, i * 16 + 3, 2, 8, menu->entries[i].label,
                          func_ov039_020bc9cc(), 0x5c);
        }
    }
    switch (menu->mode) {
    case 1:

        DrawTextAnchored(&menu->windows[3], 0x68, 0xb, 2, 0x10, menu->extraLabels[0]);
        DrawTextAnchored(&menu->windows[3], 0x3c, 0x1b, 2, 0x10, menu->extraLabels[1]);
        DrawTextAnchored(&menu->windows[3], 0x94, 0x1b, 2, 0x10, menu->extraLabels[2]);
        DrawTextColored(&menu->windows[2], 5, 0, 2, 10, menu->extraLabels[3]);
        break;
    case 2:
        DrawTextPackedColor(&menu->windows[3], 0, 0, 2, 6, 10, func_ov027_020ba2c8(menu->strings, menu->unlockMessage));
        break;
    case 0:
        DrawTextColored(&menu->windows[2], 5, 0, 2, 10, menu->entries[menu->cursor].description);
        break;
    }
    Text_UploadTileBuffer(&menu->windows[1]);
    Text_UploadTileBuffer(&menu->windows[2]);
    Text_UploadTileBuffer(&menu->windows[0]);
    Text_UploadTileBuffer(&menu->windows[3]);
}
