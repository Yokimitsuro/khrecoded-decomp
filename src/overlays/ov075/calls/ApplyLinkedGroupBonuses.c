#include "nitro/types.h"

typedef struct UnitStats UnitStats;
typedef struct BonusRecord BonusRecord;

typedef struct LinkEntry {
    u8 pad_00[2];
    u8 kind;
    u8 pad_03[3];
    u16 groupIndex;
} LinkEntry;

typedef struct GridLayout {
    u8 pad_00[0x9c];
    LinkEntry *entries[1];
} GridLayout;

typedef struct MatrixNode {
    u8 pad_00[4];
    s16 recordIndex;
    u16 groupIndex;
    u8 pad_08[4];
    s16 links[4];
} MatrixNode;

typedef struct NodeGroup {
    MatrixNode *nodes[20];
} NodeGroup;

typedef struct MatrixMenu {
    u8 pad_00000[0x12dd0];
    GridLayout *layout;
    MatrixNode *current;
    u8 pad_12dd8[0x12de4 - 0x12dd8];
    NodeGroup groups[1];
} MatrixMenu;

extern BonusRecord *GetRecordSlotPair0Entry(s32 index);
extern void ApplyLevelBonus(UnitStats *stats, const BonusRecord *bonus, int count);

void ApplyLinkedGroupBonuses(MatrixMenu *menu, UnitStats *stats)
{
    MatrixNode **node;
    s16 *link = menu->current->links;
    int i;

    for (i = 0; i < 4; i++, link++) {
        if (*link >= 0) {
            LinkEntry *entry = menu->layout->entries[*link];
            if (entry->kind == 1) {
                node = menu->groups[entry->groupIndex].nodes;
                break;
            }
        }
    }
    do {
        ApplyLevelBonus(stats, GetRecordSlotPair0Entry((*node)->recordIndex), 1);
        node++;
    } while (*node != NULL);
}