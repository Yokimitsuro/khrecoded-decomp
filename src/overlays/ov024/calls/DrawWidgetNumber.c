#include "nitro/types.h"

typedef struct WidgetPos {
    s32 x;
    s32 y;
} WidgetPos;

extern void *FindWidgetById(void *manager, int widgetId);
extern WidgetPos *func_ov027_020b91c8(void *manager, void *widget);
extern void func_ov027_020b9604(void *manager, void *widget);
extern void SetEntrySlotsVisible(void *manager, void *widget, int visible);
extern void func_ov027_020b96c0(void *manager, void *widget, u16 digit);
extern void func_0204f0d4(void *manager, int slot);
extern void func_0204f218(void *manager, int slot, u16 digit);
extern int CreateObjectSlot(void *manager, int resource, int layer, int x, int y, int arg5, int arg6, int digit, int arg8);

void DrawWidgetNumber(void *manager, int widgetId, int layer, int value, int spacing, int *slots, BOOL reset)
{
    void *widget;
    int offset = spacing;
    WidgetPos pos;
    int i;

    widget = FindWidgetById(manager, widgetId);
    pos = *func_ov027_020b91c8(manager, widget);

    if (reset) {
        for (i = 0; i < 10; i++) {
            if (slots[i] >= 0) {
                func_0204f0d4(manager, slots[i]);
            }
            slots[i] = -1;
        }
        func_ov027_020b9604(manager, widget);
        SetEntrySlotsVisible(manager, widget, 1);
    }
    func_ov027_020b96c0(manager, widget, value % 10);
    for (i = 0; i < 10; i++) {
        if (value >= 10) {
            if (slots[i] < 0) {
                slots[i] = CreateObjectSlot(manager, 0, layer, (pos.x >> 12) - offset, pos.y >> 12, 0, 0, value % 100 / 10, 1);
            } else {
                func_0204f218(manager, slots[i], value % 100 / 10);
            }
            value /= 10;
            offset += spacing;
        } else if (slots[i] >= 0) {
            func_0204f0d4(manager, slots[i]);
            slots[i] = -1;
        }
    }
}
