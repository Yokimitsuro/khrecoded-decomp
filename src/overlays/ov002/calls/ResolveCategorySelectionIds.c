#include "nitro/types.h"

typedef struct CategorySelection {
    u32 category6 : 5;
    u32 category17 : 5;
    u32 category12 : 6;
    u32 category20 : 7;
    u32 category21 : 7;
    u32 pad_00 : 2;
    u32 category0 : 4;
    u32 category1 : 4;
    u32 category3 : 8;
    u32 category4 : 5;
    u32 category5 : 5;
    u32 category2 : 6;
    u32 category7 : 7;
    u32 category8 : 7;
    u32 category9 : 7;
    u32 category10 : 7;
    u32 category15 : 4;
    u32 category11 : 7;
    u32 category16 : 7;
    u32 category13 : 6;
    u32 category19 : 5;
    u32 category14 : 5;
    u32 pad_0C : 2;
} CategorySelection;

typedef struct SelectionView {
    u8 pad_00[0x18];
    CategorySelection *selection;
    s32 recordIds[22];
} SelectionView;

extern s32 func_ov002_02068498(s32 category, s32 entryNumber, BOOL skipFlagCheck);

void ResolveCategorySelectionIds(SelectionView *view) {
    CategorySelection *selection = view->selection;

    view->recordIds[0] = func_ov002_02068498(0, selection->category0, TRUE);
    view->recordIds[1] = func_ov002_02068498(1, selection->category1, TRUE);
    view->recordIds[2] = func_ov002_02068498(2, selection->category2, TRUE);
    view->recordIds[3] = func_ov002_02068498(3, selection->category3, TRUE);
    view->recordIds[4] = func_ov002_02068498(4, selection->category4, TRUE);
    view->recordIds[5] = func_ov002_02068498(5, selection->category5, TRUE);
    view->recordIds[6] = func_ov002_02068498(6, selection->category6, TRUE);
    view->recordIds[7] = func_ov002_02068498(7, selection->category7, TRUE);
    view->recordIds[8] = func_ov002_02068498(8, selection->category8, TRUE);
    view->recordIds[9] = func_ov002_02068498(9, selection->category9, TRUE);
    view->recordIds[10] = func_ov002_02068498(10, selection->category10, TRUE);
    view->recordIds[11] = func_ov002_02068498(11, selection->category11, TRUE);
    view->recordIds[12] = func_ov002_02068498(12, selection->category12, TRUE);
    view->recordIds[13] = func_ov002_02068498(13, selection->category13, TRUE);
    view->recordIds[14] = func_ov002_02068498(14, selection->category14, TRUE);
    view->recordIds[15] = func_ov002_02068498(15, selection->category15, TRUE);
    view->recordIds[16] = func_ov002_02068498(16, selection->category16, TRUE);
    view->recordIds[17] = func_ov002_02068498(17, selection->category17, TRUE);
    view->recordIds[19] = func_ov002_02068498(19, selection->category19, TRUE);
    view->recordIds[20] = func_ov002_02068498(16, selection->category20, TRUE);
    view->recordIds[21] = func_ov002_02068498(16, selection->category21, TRUE);
}
