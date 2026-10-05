#include "nitro/types.h"

typedef struct Widget Widget;

typedef struct WidgetRoot {
    u8 pad_0000[0x6434];
    u8 widgetList[0xC];
} WidgetRoot;

extern Widget *NNS_FndGetNextListObject(void *list, Widget *obj);
extern BOOL IsWidgetMoveFinished(Widget *widget);

BOOL AreAllWidgetMovesFinished(WidgetRoot *root)
{
    Widget *widget;
    BOOL finished = TRUE;

    for (widget = NNS_FndGetNextListObject(root->widgetList, NULL); widget != NULL;
         widget = NNS_FndGetNextListObject(root->widgetList, widget)) {
        if (finished && IsWidgetMoveFinished(widget)) {
            finished = TRUE;
        } else {
            finished = FALSE;
        }
    }
    return finished;
}
