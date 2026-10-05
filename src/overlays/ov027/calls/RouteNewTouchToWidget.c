#include "nitro/types.h"

typedef struct InputRecord {
    u16 x;
    u16 y;
    u16 touch;
    u16 invalid;
} InputRecord;

typedef struct Widget {
    u8 pad_00[0xA8];
    void (*onTouch)(struct Widget *widget);
} Widget;

typedef struct WidgetRoot {
    u8 pad_0000[0x6434];
    u8 widgetList[0xC];
    InputRecord lastInput;
} WidgetRoot;

extern int func_ov027_020b9f9c(InputRecord *input);
extern BOOL GetLatestValidInputRecord(WidgetRoot *root, InputRecord *out);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern BOOL HitTestWidget(WidgetRoot *root, int x, int y, Widget *widget);

BOOL RouteNewTouchToWidget(WidgetRoot *root)
{
    BOOL hit = FALSE;
    InputRecord input;
    Widget *widget;

    if (func_ov027_020b9f9c(&input) == 0 && GetLatestValidInputRecord(root, &input) == 0) {
        MI_CpuCopy8(&root->lastInput, &input, sizeof(InputRecord));
    }
    if (((root->lastInput.touch ^ input.touch) & input.touch) && input.invalid == 0) {
        for (widget = NNS_FndGetNextListObject(root->widgetList, NULL); widget != NULL;
             widget = NNS_FndGetNextListObject(root->widgetList, widget)) {
            if (HitTestWidget(root, input.x, input.y, widget)) {
                MI_CpuCopy8(&input, &root->lastInput, sizeof(InputRecord));
                widget->onTouch(widget);
                hit = TRUE;
                break;
            }
        }
    }
    if (hit == FALSE) {
        MI_CpuCopy8(&input, &root->lastInput, sizeof(InputRecord));
    }
    return hit;
}
