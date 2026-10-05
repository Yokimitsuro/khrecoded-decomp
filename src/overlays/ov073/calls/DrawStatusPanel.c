#include "nitro/types.h"

typedef struct PanelElement {
    u16 unk_00;
    s16 x;
    s16 y;
} PanelElement;

typedef struct StatusMenu {
    u8 pad_0000[0xdf4];
    u8 textLayer[0x10dc - 0xdf4];
    void *tagTracker;
    void *container;
} StatusMenu;

typedef struct StatusPanel {
    u16 *labels[9];
    u8 pad_024[0x9c - 0x24];
    u16 *rowValues[8][2];
    u8 pad_0dc[0x100 - 0xdc];
    PanelElement *elements[4];
    s16 cells[6];
    u16 enabledMask;
    u16 highlightMask;
    u16 mode;
    u16 pad_122;
    BOOL locked[6];
    int rowColor;
} StatusPanel;

typedef struct RowLayout {
    u8 rows[8][3];
} RowLayout;

extern RowLayout data_ov073_020c4130;
extern s32 CheckStatusAndThreshold(void);
extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);
extern void func_ov027_020b8230(void *tracker, PanelElement *element);
extern void func_ov027_020b824c(void *tracker, PanelElement *element, s16 x, s16 y);
extern void IndexedRecords_SetFlag2(void *container, int cellIndex, BOOL visible);
extern void DrawTextAnchored(void *layer, int x, int y, int color, u32 flags, const u16 *text);

void DrawStatusPanel(StatusMenu *menu, StatusPanel *panel)
{
    RowLayout layout = data_ov073_020c4130;
    void *tracker = menu->tagTracker;
    void *container = menu->container;
    BOOL thresholdReached = CheckStatusAndThreshold() >= 2;
    s16 x;
    s16 y;
    s16 i;
    u8 *row;
    int color;
    BOOL enabled;
    BOOL highlight;
    BOOL locked;
    u16 *text;
    u8 width;
    u8 left;
    u8 top;

    panel->rowColor = 2;
    if (panel->mode == 6) {
        if (ReadGlobalPackedBits(ReadGlobalPackedBits(0x1a00, 2) * 0xf00 + 0x3700, 0x10) != 100
            && ReadGlobalPackedBits(0x1a00, 2) != 3) {
            panel->rowColor = 8;
        }
    }

    x = panel->elements[0]->x;
    y = panel->elements[0]->y;
    func_ov027_020b8230(tracker, panel->elements[0]);
    func_ov027_020b824c(tracker, panel->elements[0], x, y + 2);

    x = panel->elements[1]->x;
    y = panel->elements[1]->y;
    func_ov027_020b8230(tracker, panel->elements[1]);
    y += 2;
    func_ov027_020b824c(tracker, panel->elements[1], x, y);
    y += 2;
    func_ov027_020b824c(tracker, panel->elements[1], x, y);
    y += 2;
    func_ov027_020b824c(tracker, panel->elements[1], x, y);

    func_ov027_020b8230(tracker, panel->elements[2]);

    x = panel->elements[3]->x;
    y = panel->elements[3]->y;
    func_ov027_020b8230(tracker, panel->elements[3]);
    func_ov027_020b824c(tracker, panel->elements[3], x, y + 2);

    DrawTextAnchored(menu->textLayer, 0x20, 0x43, 2, 0x10, panel->labels[0]);

    row = layout.rows[0];
    for (i = 0; i < sizeof(layout.rows) / sizeof(layout.rows[0]); i++) {
        enabled = FALSE;
        highlight = FALSE;
        locked = FALSE;
        if (i == 5 && thresholdReached) {
            color = 0xe;
        } else if (i < 6) {
            color = panel->rowColor;
        } else {
            color = 2;
        }
        DrawTextAnchored(menu->textLayer, row[0], row[2], 6, 8, panel->labels[i + 1]);
        if (i < 6) {
            enabled = (panel->enabledMask & (1 << i)) ? TRUE : FALSE;
            highlight = ((1 << i) & panel->highlightMask) ? TRUE : FALSE;
            locked = panel->locked[i];
            IndexedRecords_SetFlag2(container, panel->cells[i], enabled);
            if (enabled) {
                DrawTextAnchored(menu->textLayer, row[0] + row[1] - 0x20, row[2], 2, 0x20, panel->rowValues[i][0]);
            }
        }
        text = panel->rowValues[i][enabled];
        left = row[0];
        width = row[1];
        top = row[2];
        if (locked) {
            color = 10;
        } else if (enabled) {
            color = highlight ? 8 : 6;
        }
        DrawTextAnchored(menu->textLayer, left + width, top, color, 0x20, text);
        row += 3;
    }
}
