#include "nitro/types.h"

typedef struct SelectionView {
    u8 pad_00[0x18];
    void *selection;
    s32 recordIds[22];
    u8 objSlots[22][16];
    u8 recordSlots[22][16];
    u8 extraSlots[22][16];
    u8 counts[22];
} SelectionView;

extern s32 data_ov002_0206af0c[];
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void ResolveCategorySelectionIds(SelectionView *view);

void ResetSelectionView(SelectionView *view)
{
    int i = 0;

    MI_CpuFill8(view->recordIds, 0, sizeof(view->recordIds));
    MI_CpuFill8(view->objSlots, 0, sizeof(view->objSlots));
    MI_CpuFill8(view->recordSlots, 0, sizeof(view->recordSlots));
    MI_CpuFill8(view->extraSlots, 0, sizeof(view->extraSlots));
    MI_CpuFill8(view->counts, 0, sizeof(view->counts));
    if (view->selection == NULL) {
        for (; i < 20; i++) {
            view->recordIds[i] = data_ov002_0206af0c[i];
        }
    } else {
        ResolveCategorySelectionIds(view);
    }
}
