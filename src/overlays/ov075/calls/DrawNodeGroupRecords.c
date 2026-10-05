#include "nitro/types.h"

typedef struct MatrixNode {
    u8 pad_00[4];
    s16 recordIndex;
    u16 groupIndex;
} MatrixNode;

typedef struct NodeGroup {
    MatrixNode *nodes[20];
} NodeGroup;

typedef struct MatrixMenu {
    u8 pad_00000[0x12dd4];
    MatrixNode *current;
    u8 pad_12dd8[0x12de4 - 0x12dd8];
    NodeGroup groups[1];
} MatrixMenu;

extern void *GetRecordSlotPair0Entry(s32 index);
extern void ApplyLevelBonus(void *target, void *record, u8 kind);

void DrawNodeGroupRecords(MatrixMenu *menu, void *target, int defaultIndex)
{
    MatrixNode *current = menu->current;
    MatrixNode **node = menu->groups[current->groupIndex].nodes;

    do {
        u8 kind = (current == *node) + 1;
        int index;

        if (kind != 1) {
            index = defaultIndex;
        } else {
            index = (*node)->recordIndex;
        }
        ApplyLevelBonus(target, GetRecordSlotPair0Entry(index), kind);
        node++;
    } while (*node != NULL);
}