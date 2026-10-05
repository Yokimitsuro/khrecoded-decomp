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


int CountFilledCategorySelections(CategorySelection *selection) {
    int count;

    count = selection->category3 != 0;
    count += selection->category4 != 0;
    count += selection->category5 != 0;
    count += selection->category6 != 0;
    count += selection->category7 != 0;
    count += selection->category8 != 0;
    count += selection->category9 != 0;
    count += selection->category10 != 0;
    count += selection->category11 != 0;
    count += selection->category12 != 0;
    count += selection->category13 != 0;
    count += selection->category14 != 0;
    count += selection->category15 != 0;
    count += selection->category16 != 0;
    count += selection->category17 != 0;
    count += selection->category19 != 0;
    count += selection->category20 != 0;
    count += selection->category21 != 0;
    return count;
}
