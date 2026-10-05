#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScreenPoint {
    fx32 x;
    fx32 y;
} ScreenPoint;

extern void func_0204f0d4(void *objects, int slotIndex);
extern void *FindWidgetById(void *objects, int id);
extern ScreenPoint *func_ov027_020b91c8(void *objects, void *widget);
extern void func_ov027_020b9604(void *objects, void *widget);
extern void func_ov027_020b96c0(void *objects, void *widget, int frame);
extern void SetEntrySlotsVisible(void *objects, void *widget, int visible);
extern int CreateObjectSlot_020bdec4(void *manager, int animation, int resource, int x, int y, int mode,
                                     int priority, int palette, int enabled);

void DrawResultsCounter(void *objects, int id, int resource, int value, int spacing, int *slots)
{
    int count;
    int i;
    void *widget;
    ScreenPoint pos;
    int offset;

    count = 0;
    offset = spacing;
    for (i = 0; i < 10; i++) {
        if (slots[i] >= 0) {
            func_0204f0d4(objects, slots[i]);
        }
        slots[i] = -1;
    }
    widget = FindWidgetById(objects, id);
    pos = *func_ov027_020b91c8(objects, widget);
    func_ov027_020b9604(objects, widget);
    func_ov027_020b96c0(objects, widget, (u16)(value % 10));
    SetEntrySlotsVisible(objects, widget, 1);
    for (i = 0; i < 10; i++) {
        if (value < 10) {
            return;
        }
        slots[count++] = CreateObjectSlot_020bdec4(objects, 0, resource, (pos.x >> 12) - offset, pos.y >> 12, 1, 1,
                                                   value % 100 / 10, 1);
        value /= 10;
        offset += spacing;
    }
}
