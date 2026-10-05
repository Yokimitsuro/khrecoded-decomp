#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_0000[0xcb50];
    u8 *groupEntries[0x14];
    u8 entryStorage[0xcf2c - 0xcba0];
    u8 groupCounts[0x14];
    s16 groupSelections[0x14];
} PanelState;

extern PanelState *data_ov014_0206f9a0;
extern u16 data_ov014_0206f838[];
extern u8 data_ov014_0206f808[];

extern void *func_ov002_02066fc8(void);
extern void MI_CpuFill8(void *dst, int value, int size);
extern BOOL IsCategoryEntryFlagSet(int category, int entry);
extern int GetPackedField(void *info, int category, int entry);
extern BOOL CheckRecordEntryRequirements(int entry);

void BuildPanelGroupEntries(void)
{
    void *info = func_ov002_02066fc8();
    int group;
    int entry;
    int count;
    int entryCount;
    u8 *entries;

    MI_CpuFill8(data_ov014_0206f9a0->groupSelections, 0xff, sizeof(data_ov014_0206f9a0->groupSelections));
    for (group = 0; group < 0x14; group++) {
        data_ov014_0206f9a0->groupEntries[group] = data_ov014_0206f9a0->entryStorage + data_ov014_0206f838[group];
    }
    for (group = 0; group < 0x14; group++) {
        count = 0;
        if (group != 0x12) {
            entries = data_ov014_0206f9a0->groupEntries[group];
            entryCount = data_ov014_0206f808[group];
            for (entry = count; entry < entryCount; entry++) {
                if (IsCategoryEntryFlagSet(group, entry)) {
                    entries[count] = entry;
                    if (data_ov014_0206f9a0->groupSelections[group] < 0 &&
                        entry == GetPackedField(info, group, entry)) {
                        data_ov014_0206f9a0->groupSelections[group] = count;
                    }
                    count++;
                }
            }
        } else {
            entries = data_ov014_0206f9a0->groupEntries[0x12];
            for (entry = count; entry < 0x5d; entry++) {
                if (CheckRecordEntryRequirements(entry)) {
                    entries[count++] = entry;
                }
            }
        }
        data_ov014_0206f9a0->groupCounts[group] = count;
    }
    for (group = 0; group < 0x14; group++) {
        if (data_ov014_0206f9a0->groupSelections[group] < 0) {
            data_ov014_0206f9a0->groupSelections[group] = 0;
        }
    }
}
