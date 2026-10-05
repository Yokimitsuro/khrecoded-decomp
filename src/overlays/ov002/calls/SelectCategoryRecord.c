#include "nitro/types.h"

typedef struct RecordSet {
    u8 pad_00[0xc];
    u32 low : 30;
    u32 hasExtra : 1;
    u32 high : 1;
} RecordSet;

typedef struct RecordB {
    u8 pad_00[0xc];
    s32 category;
} RecordB;

typedef struct IconOffset {
    s32 x;
    s32 y;
} IconOffset;

typedef struct SelectionView {
    u8 pad_00[8];
    IconOffset iconOffset;
    u8 pad_10[8];
    RecordSet *selection;
    u8 pad_1c[0x4ab - 0x1c];
    u8 flags_b0 : 4;
    u8 ready : 1;
    u8 flags_b5 : 1;
    u8 inSpecialRange : 1;
    u8 flags_b7 : 1;
} SelectionView;

extern s32 data_ov002_0206aebc[];
extern int AcquireRecordSlot(int slot, int param);
extern void ReleaseRecordSlot(s32 slot);
extern RecordB *GetRecordTableBEntry(s32 index);
extern BOOL ApplyCategoryRecord(RecordSet *set, int category, int offset);
extern void ResetSelectionView(SelectionView *view);
extern void func_ov002_02069df8(int category, int index, IconOffset *out);
extern void func_ov002_02067c10(void *manager, SelectionView *view);

void SelectCategoryRecord(void *manager, SelectionView *view, s32 recordId)
{
    int category;
    int offset;
    BOOL inRange;

    AcquireRecordSlot(9, 1);
    category = GetRecordTableBEntry(recordId)->category - 1;
    offset = recordId - data_ov002_0206aebc[category];
    ReleaseRecordSlot(9);
    view->selection->hasExtra = 1;
    ApplyCategoryRecord(view->selection, category, offset);
    ResetSelectionView(view);
    inRange = TRUE;
    if (category < 1 || category >= 6) {
        inRange = FALSE;
    }
    view->inSpecialRange = (u8)inRange;
    func_ov002_02069df8(category, offset, &view->iconOffset);
    view->ready = 1;
    func_ov002_02067c10(manager, view);
}
