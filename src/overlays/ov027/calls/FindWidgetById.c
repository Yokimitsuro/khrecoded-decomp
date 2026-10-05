#include "nitro/types.h"

typedef struct Widget {
    u8 pad_00[0xC];
    int id;
} Widget;

typedef struct WidgetRoot {
    u8 pad_0000[0x6434];
    u8 widgetList[0xC];
} WidgetRoot;

extern Widget *NNS_FndGetNextListObject(void *list, Widget *obj);

Widget *FindWidgetById(WidgetRoot *root, int id)
{
    Widget *widget = NULL;

    if (id >= 0) {
        for (widget = NNS_FndGetNextListObject(root->widgetList, NULL); widget != NULL;
             widget = NNS_FndGetNextListObject(root->widgetList, widget)) {
            if (widget->id == id) {
                break;
            }
        }
    }
    return widget;
}
