#include "nitro/types.h"

extern s32 GetPackedFieldValue(u32 target, s32 category, s32 flag);
extern void ApplyGroupElements(u32 param1, u32 param2, s32 category, u32 param4);

void SyncMismatchedCategoryEntries(u32 param1, u32 param2, u32 param3, u32 param4) {
    s32 category = 3;
    s32 valueA;
    s32 valueB;

    do {
        valueA = GetPackedFieldValue(*(u32 *)(param2 + 0x18), category, 1);
        valueB = GetPackedFieldValue(param3, category, 1);
        if (valueA != 0 && valueA != valueB) {
            ApplyGroupElements(param1, param2, category, param4);
        }
        category = category + 1;
    } while (category < 0x16);
}
