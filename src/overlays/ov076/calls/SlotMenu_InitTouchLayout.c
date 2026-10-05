#include "nitro/types.h"

typedef struct TouchRect {
    s32 x;
    s32 y;
    s32 enabled;
    s32 frame;
    s32 tag;
    s32 group;
} TouchRect;

typedef struct SlotPageLayout {
    TouchRect rects[18];
} SlotPageLayout;

typedef struct SlotMenu {
    u8 pad_00000[0x1b914];
    SlotPageLayout pages[8];
    TouchRect buttons[4];
} SlotMenu;

typedef struct SaveData {
    u8 pad_0000[0x2c68];
    u8 slotLimit;
} SaveData;

extern SaveData *data_0205fe0c;
extern int func_ov039_020bc1dc(void);
extern int FindWidgetById(int panel, int elementId);
extern void SetEntrySlotsVisible(int panel, int element, BOOL visible);
extern void func_ov027_020b97d8(int context, int record, int mode);


void SlotMenu_InitTouchLayout(SlotMenu *menu)
{
    u32 visibleCount = data_0205fe0c->slotLimit + 3;
    int page;
    int panel;
    int elementId;
    int element;

    for (page = 0; page < 8; page++) {
        TouchRect *rects = menu->pages[page].rects;

        rects[0].x = 0x18;
        rects[0].y = page * 64 + 0x18;
        rects[0].enabled = 0;
        rects[0].frame = 0x1a;
        rects[0].tag = -1;
        rects[0].group = -1;
        rects[1].x = 0xac;
        rects[1].y = page * 64 + 0x14;
        rects[1].enabled = 0;
        rects[1].frame = 0x1e;
        rects[1].tag = -1;
        rects[1].group = -1;
        rects[2].x = 0xb0;
        rects[2].y = page * 64 + 0x14;
        rects[2].enabled = 0;
        rects[2].frame = 0x1e;
        rects[2].tag = -1;
        rects[2].group = -1;
        rects[3].x = 0xb4;
        rects[3].y = page * 64 + 0x14;
        rects[3].enabled = 0;
        rects[3].frame = 0x1e;
        rects[3].tag = -1;
        rects[3].group = -1;
        rects[4].x = 0xb8;
        rects[4].y = page * 64 + 0x14;
        rects[4].enabled = 0;
        rects[4].frame = 0x1e;
        rects[4].tag = -1;
        rects[4].group = -1;
        rects[6].x = 0xaa;
        rects[6].y = page * 64 + 0xe;
        rects[6].enabled = 0;
        rects[6].frame = 0x1c;
        rects[6].tag = -1;
        rects[6].group = -1;
        rects[5].x = 0xaa;
        rects[5].y = page * 64 + 0xe;
        rects[5].enabled = 0;
        rects[5].frame = 0x1d;
        rects[5].tag = -1;
        rects[5].group = -1;
        rects[7].x = 0xac;
        rects[7].y = page * 64 + 0x24;
        rects[7].enabled = 0;
        rects[7].frame = 0x1e;
        rects[7].tag = -1;
        rects[7].group = -1;
        rects[8].x = 0xb0;
        rects[8].y = page * 64 + 0x24;
        rects[8].enabled = 0;
        rects[8].frame = 0x1e;
        rects[8].tag = -1;
        rects[8].group = -1;
        rects[9].x = 0xb4;
        rects[9].y = page * 64 + 0x24;
        rects[9].enabled = 0;
        rects[9].frame = 0x1e;
        rects[9].tag = -1;
        rects[9].group = -1;
        rects[10].x = 0xb8;
        rects[10].y = page * 64 + 0x24;
        rects[10].enabled = 0;
        rects[10].frame = 0x1e;
        rects[10].tag = -1;
        rects[10].group = -1;
        rects[12].x = 0xaa;
        rects[12].y = page * 64 + 0x1e;
        rects[12].enabled = 0;
        rects[12].frame = 0x1c;
        rects[12].tag = -1;
        rects[12].group = -1;
        rects[11].x = 0xaa;
        rects[11].y = page * 64 + 0x1e;
        rects[11].enabled = 0;
        rects[11].frame = 0x1d;
        rects[11].tag = -1;
        rects[11].group = -1;
        rects[13].x = 0xa2;
        rects[13].y = page * 64 + 0x11;
        rects[13].enabled = 0;
        rects[13].frame = 0x20;
        rects[13].tag = -1;
        rects[13].group = -1;
        rects[14].x = 0xa2;
        rects[14].y = page * 64 + 0x21;
        rects[14].enabled = 0;
        rects[14].frame = 0x20;
        rects[14].tag = -1;
        rects[14].group = -1;
        rects[15].x = 0xb2;
        rects[15].y = page * 64 + 0x31;
        rects[15].enabled = 0;
        rects[15].frame = 0x20;
        rects[15].tag = -1;
        rects[15].group = -1;
        rects[16].x = 0xb4;
        rects[16].y = page * 64 + 0x11;
        rects[16].enabled = 0;
        rects[16].frame = 0x1b;
        rects[16].tag = -1;
        rects[16].group = -1;
        rects[17].x = 0xb4;
        rects[17].y = page * 64 + 0x21;
        rects[17].enabled = 0;
        rects[17].frame = 0x1b;
        rects[17].tag = -1;
        rects[17].group = -1;
        rects[0].enabled = page < visibleCount;
        rects[0].tag = page;
    }

    menu->buttons[0].x = 0;
    menu->buttons[0].y = 0;
    menu->buttons[0].enabled = 0;
    menu->buttons[0].frame = 0;
    menu->buttons[0].tag = -1;
    menu->buttons[0].group = -1;
    menu->buttons[1].x = 0;
    menu->buttons[1].y = 0;
    menu->buttons[1].enabled = 0;
    menu->buttons[1].frame = 2;
    menu->buttons[1].tag = -1;
    menu->buttons[1].group = -1;
    menu->buttons[2].x = 0;
    menu->buttons[2].y = 0;
    menu->buttons[2].enabled = 0;
    menu->buttons[2].frame = 3;
    menu->buttons[2].tag = -1;
    menu->buttons[2].group = -1;
    menu->buttons[3].x = 0;
    menu->buttons[3].y = 0;
    menu->buttons[3].enabled = 0;
    menu->buttons[3].frame = 4;
    menu->buttons[3].tag = -1;
    menu->buttons[3].group = -1;

    panel = func_ov039_020bc1dc();
    for (elementId = 100; elementId <= 0x76; elementId++) {
        element = FindWidgetById(panel, elementId);
        if (element != 0) {
            func_ov027_020b97d8(panel, element, 1);
        }
    }
    SetEntrySlotsVisible(panel, FindWidgetById(panel, 6), 0);
    SetEntrySlotsVisible(panel, FindWidgetById(panel, 0), 0);
    func_ov027_020b97d8(panel, FindWidgetById(panel, 0x2a), 1);
}
