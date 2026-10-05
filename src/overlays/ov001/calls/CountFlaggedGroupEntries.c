#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x2888];
    u16 groupMasks[1];
} SaveData;

extern SaveData *data_0205fe0c;
extern BOOL IsGroupEntryFlagged(int group, int index);

int CountFlaggedGroupEntries(int group)
{
    u32 index;
    int count = 0;

    for (index = 0; index < 16; index++) {
        if ((1 << index) & data_0205fe0c->groupMasks[group]) {
            if (IsGroupEntryFlagged(group, index)) {
                count++;
            }
        }
    }
    return count;
}
