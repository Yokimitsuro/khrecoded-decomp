#include "nitro/types.h"

typedef struct LinkEntry {
    u8 pad_00[2];
    u8 kind;
    s8 unlockBit;
} LinkEntry;

typedef struct GridLayout {
    u8 pad_00[0x9c];
    LinkEntry *entries[1];
} GridLayout;

typedef struct MatrixNode {
    u8 pad_00[6];
    u16 groupIndex;
    u8 pad_08[4];
    s16 links[4];
} MatrixNode;

typedef struct MatrixMenu {
    u8 pad_00000[0x12dd0];
    GridLayout *layout;
} MatrixMenu;

typedef struct SaveData {
    u8 pad_0000[0x2c5c];
    int unlockBits[1];
} SaveData;

extern SaveData *data_0205fe0c;
extern int GetPackedBitMask(int *bitWords, int bitIndex);

int GetNodeGroupIfUnlocked(MatrixMenu *menu, MatrixNode *node)
{
    s16 *link = node->links;
    int remaining;

    for (remaining = 4; remaining > 0; remaining--, link++) {
        if (*link >= 0) {
            LinkEntry *entry = menu->layout->entries[*link];
            if (entry->kind >= 0xe && entry->unlockBit >= 0) {
                BOOL unlocked = GetPackedBitMask(data_0205fe0c->unlockBits, entry->unlockBit) ? TRUE : FALSE;
                if (!unlocked) {
                    return -1;
                }
            }
        }
    }
    return node->groupIndex;
}