#include "nitro/types.h"

typedef struct RecordPreset {
    u8 pad_00[0xe];
    s16 recordIds[0x14];
} RecordPreset;

extern s32 data_ov002_0206ae70[];
extern unsigned int func_0202a9e4(unsigned int range);
extern void func_ov002_0206aaa0(s32 *preferredItemIds);
extern s32 func_ov002_0206a888(s32 category, s32 *preferredItemIds);
extern void func_ov002_020687a4(void *dest, s32 *recordIds, int count);

void FillCategoryRecords(void *dest, RecordPreset *preset)
{
    s32 recordId;
    s32 preferred[6];
    s16 *ids;
    int i;
    s32 category;
    int roll;
    int chance;

    if (preset != NULL) {
        ids = preset->recordIds;
        for (i = 0; i < 0x14; i++) {
            if (i != 0x12 && (recordId = ids[i]) != -1) {
                func_ov002_020687a4(dest, &recordId, 1);
            }
        }
        return;
    }
    roll = func_0202a9e4(100);
    func_ov002_0206aaa0(preferred);
    for (i = 0; i < 0x13; i++) {
        chance = func_0202a9e4(100);
        category = data_ov002_0206ae70[i];
        if (category >= 4 && chance < 0x28) {
            continue;
        }
        if (i == 8 && roll < 0x46) {
            continue;
        }
        if (i == 0x12 && roll >= 10) {
            continue;
        }
        recordId = func_ov002_0206a888(category, func_0202a9e4(100) < 0x46 ? preferred : NULL);
        func_ov002_020687a4(dest, &recordId, 1);
    }
}
