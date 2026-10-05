#include "nitro/types.h"

typedef struct {
    s16 x;
    s16 y;
} PanelPoint;

typedef struct {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} MaskRect;

typedef struct {
    s16 state;
    u8 pad_02[6];
    int radius;
    u8 pad_0c[0xc];
} PanelSlot;

typedef struct {
    int ids[6];
} WidgetIdTable;

typedef struct {
    int x;
    int y;
} WidgetPos;

typedef struct {
    u8 pad_00[0x24];
    int startX;
    int startY;
    int endX;
    int endY;
} Widget;

typedef struct {
    int timer;
    u8 pad_04[0x51];
    s8 slotCount;
    u8 pad_56[0x2e];
    PanelSlot slots[9];
    u8 pad_15c[4];
    u8 panel[0x65dc - 0x160];
    void *list;
    u8 pad_65e0[0xbd38 - 0x65e0];
    u8 mask[0x10e38 - 0xbd38];
    u8 grid[1];
} PanelBoard;

extern PanelBoard *data_ov015_020812e0;
extern PanelPoint *gWirelessModeDataTables[];
extern const WidgetIdTable data_ov015_0207a2f8;
extern BOOL ClearCircleMask(MaskRect *rect, u8 *mask, int radius);
extern Widget *FindWidgetById(void *panel, int elementId);
extern void func_ov027_020b9380(void *panel, Widget *widget, WidgetPos *pos, int flag);
extern void SetEntrySlotsVisible(void *panel, Widget *widget, int visible);
extern void ConvertTileGrid(u8 *dst, u8 *src, u32 command, int tileOffset);
extern void NNS_FndInitListWithOffset0_0204f130(void *list);

void UpdatePanelBoard(void)
{
    MaskRect rect;
    WidgetPos pos;
    WidgetIdTable table;
    int i;
    int slotCount;
    PanelPoint *points;
    Widget *widget;
    BOOL inX;
    BOOL inY;

    slotCount = data_ov015_020812e0->slotCount;
    points = gWirelessModeDataTables[slotCount];
    for (i = 0; i < slotCount; i++) {
        if (data_ov015_020812e0->slots[i].state == 2) {
            rect.x = points[i].x;
            rect.y = points[i].y;
            rect.width = 0x28;
            rect.height = 0x28;
            data_ov015_020812e0->slots[i].radius += 2;
            if (ClearCircleMask(&rect, data_ov015_020812e0->mask, data_ov015_020812e0->slots[i].radius)) {
                data_ov015_020812e0->slots[i].state = 3;
            }
        }
    }
    table = data_ov015_0207a2f8;
    for (i = 0; i < 6; i++) {
        widget = FindWidgetById(data_ov015_020812e0->panel, table.ids[i]);
        if (widget != NULL) {
            inX = FALSE;
            inY = FALSE;
            func_ov027_020b9380(data_ov015_020812e0->panel, widget, &pos, 0);
            if (widget->startX < widget->endX) {
                if (widget->startX < pos.x && pos.x < widget->endX) {
                    inX = TRUE;
                }
            } else if (widget->startX > widget->endX) {
                if (widget->startX > pos.x && pos.x > widget->endX) {
                    inX = TRUE;
                }
            } else {
                inX = TRUE;
            }
            if (widget->startY < widget->endY) {
                if (widget->startY < pos.y && pos.y < widget->endY) {
                    inY = TRUE;
                }
            } else if (widget->startY > widget->endY) {
                if (widget->startY > pos.y && pos.y > widget->endY) {
                    inY = TRUE;
                }
            } else {
                inY = TRUE;
            }
            SetEntrySlotsVisible(data_ov015_020812e0->panel, widget, inX & inY);
        }
    }
    if (data_ov015_020812e0->timer < 200) {
        ConvertTileGrid(data_ov015_020812e0->grid, data_ov015_020812e0->mask, 0x17, 1);
    }
    NNS_FndInitListWithOffset0_0204f130(data_ov015_020812e0->list);
}
