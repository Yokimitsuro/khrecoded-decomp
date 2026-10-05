#include "nitro/types.h"

typedef struct CategorySelection {
    u32 category6 : 5;
    u32 category17 : 5;
    u32 category12 : 6;
    u32 category20 : 7;
    u32 category21 : 7;
    u32 pad_00 : 2;
    u32 unk_04 : 8;
    u32 category3 : 8;
    u32 category4 : 5;
    u32 category5 : 5;
    u32 pad_04 : 6;
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

extern int AcquireRecordSlot(int slot, int param);
extern BOOL ReleaseRecordSlot(s32 slot);
extern BOOL IsCategoryEntryFlagSet(s32 category, s32 entryIndex);

int CountFlaggedCategorySelections(CategorySelection *selection) {
    int count;
    int last;

    AcquireRecordSlot(9, 1);
    count = IsCategoryEntryFlagSet(3, selection->category3 - 1);
    count += IsCategoryEntryFlagSet(4, selection->category4 - 1);
    count += IsCategoryEntryFlagSet(5, selection->category5 - 1);
    count += IsCategoryEntryFlagSet(6, selection->category6 - 1);
    count += IsCategoryEntryFlagSet(7, selection->category7 - 1);
    count += IsCategoryEntryFlagSet(8, selection->category8 - 1);
    count += IsCategoryEntryFlagSet(9, selection->category9 - 1);
    count += IsCategoryEntryFlagSet(10, selection->category10 - 1);
    count += IsCategoryEntryFlagSet(11, selection->category11 - 1);
    count += IsCategoryEntryFlagSet(12, selection->category12 - 1);
    count += IsCategoryEntryFlagSet(13, selection->category13 - 1);
    count += IsCategoryEntryFlagSet(14, selection->category14 - 1);
    count += IsCategoryEntryFlagSet(15, selection->category15 - 1);
    count += IsCategoryEntryFlagSet(16, selection->category16 - 1);
    count += IsCategoryEntryFlagSet(17, selection->category17 - 1);
    count += IsCategoryEntryFlagSet(19, selection->category19 - 1);
    count += IsCategoryEntryFlagSet(20, selection->category20 - 1);
    last = IsCategoryEntryFlagSet(21, selection->category21 - 1);
    ReleaseRecordSlot(9);
    return count + last;
}
