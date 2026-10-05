#include "nitro/types.h"

typedef struct Widget {
    u8 pad_00[0x14];
    int slots[2];
    u8 pad_1C[0x28];
    u32 idleAnims[2];
    u32 focusAnims[2];
} Widget;

extern void SetSlotAnimSequence(void *root, int slot, u32 sequence);

void ApplyWidgetFocusAnims(void *root, Widget *widget, BOOL focused)
{
    u32 *anims;
    int slot;
    int i;

    if (focused != 0) {
        anims = widget->focusAnims;
    } else {
        anims = widget->idleAnims;
    }
    for (i = 0; i < 2; i++) {
        u32 sequence = anims[i];

        if (widget != NULL && (slot = widget->slots[i]) != -1 && sequence != 0xFFFFFFFF) {
            SetSlotAnimSequence(root, slot, sequence);
        }
    }
}
