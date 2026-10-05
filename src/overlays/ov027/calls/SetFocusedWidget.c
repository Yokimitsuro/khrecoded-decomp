#include "nitro/types.h"

typedef struct Widget {
    u8 pad_00[0x14];
    int slots[2];
    u8 pad_1C[0x28];
    u32 idleAnims[2];
    u32 focusAnims[2];
} Widget;

typedef struct WidgetRoot {
    u8 pad_0000[0x646C];
    Widget *focused;
} WidgetRoot;

extern void SetSlotAnimSequence(WidgetRoot *root, int slot, u32 sequence);

void SetFocusedWidget(WidgetRoot *root, Widget *widget)
{
    int i = 0;
    Widget *previous = root->focused;

    for (; i < 2; i++) {
        if (previous != NULL) {
            if (previous->slots[i] != -1 && previous->idleAnims[i] != 0xFFFFFFFF &&
                previous->focusAnims[i] != 0xFFFFFFFF) {
                SetSlotAnimSequence(root, previous->slots[i], previous->idleAnims[i]);
            }
        }
        if (widget != NULL) {
            if (widget->slots[i] != -1 && widget->focusAnims[i] != 0xFFFFFFFF) {
                SetSlotAnimSequence(root, widget->slots[i], widget->focusAnims[i]);
            }
        }
        root->focused = widget;
    }
}
