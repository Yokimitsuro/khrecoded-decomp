#include "nitro/types.h"

typedef struct RowEntry {
    u16 value;
    u16 y;
    u16 width;
    u16 depth;
} RowEntry;

typedef struct RowTable {
    u8 pad_00[6];
    u16 count;
    RowEntry entries[1];
} RowTable;

typedef struct ListNode {
    u8 pad_00[4];
    u16 id;
    u16 parentRow;
    u16 childRow;
    u16 depth;
} ListNode;

typedef struct NodeTable {
    u8 pad_00[6];
    u16 count;
    ListNode *nodes[1];
} NodeTable;

typedef struct ListData {
    u8 pad_00[2];
    u16 baseTile;
    RowTable *rows;
    NodeTable *nodes;
} ListData;

typedef struct ListPanel {
    u8 pad_00[4];
    ListData *list;
    u8 pad_08[4];
    int screen;
    u8 pad_10[0x60];
    ListNode *path[3];
    u8 level;
    u8 pad_7d[3];
    u8 *rowStates;
    u8 *nodeStates;
    u8 pad_88[0x18];
    int locked;
    int selectedIndex;
} ListPanel;

extern void RebuildSlotChain_020c2e68(ListPanel *panel, int arg1, int arg2);
extern void DrawListSlotTiles(ListPanel *panel, u16 value, int screen, u16 y, u16 width, u16 tile, u16 palette);
extern void RefreshListRowColors(ListPanel *panel);

void RefreshListRowStates(ListPanel *panel, int arg1, int arg2)
{
    RowTable *rows;
    NodeTable *nodes;
    RowEntry *entry;
    int i;
    u16 tile;
    u16 palette;
    int selDepth;
    ListNode *node;
    u8 *nodeStates;
    u16 parent;
    int parentDepth;
    u8 *rowStates;
    u16 child;
    u8 state;

    rows = panel->list->rows;
    selDepth = (rows->entries[panel->selectedIndex].y - 2) / 16;
    panel->rowStates[0] = 0;
    for (i = 1; i < rows->count; i++) {
        if (rows->entries[i].depth - 1 > panel->level) {
            panel->rowStates[i] = 3;
        } else {
            panel->rowStates[i] = 2;
        }
    }
    nodes = panel->list->nodes;
    for (i = 0; i < nodes->count; i++) {
        ListNode *node = nodes->nodes[i];
        if (node->depth - 1 > panel->level) {
            panel->nodeStates[i] = 2;
        } else {
            panel->nodeStates[i] = 3;
        }
    }
    for (i = 0; i < *(volatile u16 *)&nodes->count; i++) {
        node = nodes->nodes[i];
        nodeStates = panel->nodeStates;
        if (nodeStates[i] != 2) {
            parent = node->parentRow;
            parentDepth = (rows->entries[parent].y - 2) / 16;
            child = node->childRow;
            rowStates = panel->rowStates;
            state = rowStates[parent];
            if ((rows->entries[child].y - 2) / 16 <= selDepth) {
                if (node->id == panel->path[parentDepth]->id) {
                    rowStates[child] = 0;
                    panel->nodeStates[i] = 0;
                }
            } else if (state != 2 && state != 3) {
                nodeStates[i] = 1;
                if (state != 2 && state != 3) {
                    panel->rowStates[child] = 1;
                }
            }
        }
    }
    RebuildSlotChain_020c2e68(panel, arg1, arg2);
    for (i = 0; i < rows->count; i++) {
        entry = &rows->entries[i];
        switch (panel->rowStates[i]) {
        case 0:
            tile = panel->list->baseTile + i * 0x18;
            if (panel->locked != 0) {
                palette = 9;
            } else {
                palette = (i == panel->selectedIndex) ? 10 : 9;
            }
            break;
        case 1:
            tile = panel->list->baseTile + i * 0x18;
            palette = 0xc;
            break;
        case 2:
            tile = panel->list->baseTile + i * 0x18;
            palette = 0xb;
            break;
        case 3:
            tile = 1;
            palette = 0xb;
            break;
        }
        DrawListSlotTiles(panel, entry->value, panel->screen, entry->y, entry->width, tile, palette);
    }
    for (i = 0; i < selDepth; i++) {
        int row = panel->path[i]->parentRow;
        entry = &rows->entries[row];
        DrawListSlotTiles(panel, entry->value, panel->screen, entry->y, entry->width,
                            panel->list->baseTile + row * 0x18, panel->locked != 0 ? 9 : 10);
    }
    RefreshListRowColors(panel);
}
