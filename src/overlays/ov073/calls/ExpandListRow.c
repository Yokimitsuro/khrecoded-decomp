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
    volatile u16 count;
    ListNode *nodes[1];
} NodeTable;

typedef struct ListData {
    u8 pad_00[2];
    u16 baseTile;
    RowTable *rows;
    NodeTable *nodes;
} ListData;

typedef struct ListPanel {
    void (*onChange)(void);
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

extern void RebuildSlotChain_020c2e68(ListPanel *panel, int depth, ListNode **saved);
extern void DrawListSlotTiles(ListPanel *panel, u16 value, int screen, u16 y, u16 width, u16 tile, u16 palette);
extern void RefreshListRowColors(ListPanel *panel);

BOOL ExpandListRow(ListPanel *panel, int row)
{
    int parentRow;
    int baseTile = panel->list->baseTile;
    NodeTable *nodes = panel->list->nodes;
    RowTable *rows = panel->list->rows;
    BOOL found = FALSE;
    ListNode *saved[3] = {NULL, NULL, NULL};
    int selDepth = (rows->entries[panel->selectedIndex].y - 2) / 16;
    int depth = (rows->entries[row].y - 2) / 16;
    int i;
    int level;
    int tile;
    int palette;
    RowEntry *entry;
    ListNode *node;

    if (depth <= selDepth || depth == 0) {
        return FALSE;
    }
    if (panel->path[depth - 1] != NULL) {
        parentRow = panel->path[depth - 1]->parentRow;
        for (i = 0; i < nodes->count; i++) {
            node = nodes->nodes[i];
            if (parentRow == node->parentRow && row == node->childRow) {
                found = TRUE;
                break;
            }
        }
        if (!found) {
            return FALSE;
        }
        for (i = 0; i < rows->count; i++) {
            entry = &rows->entries[i];
            if ((entry->y - 2) / 16 > selDepth) {
                if (panel->rowStates[i] == 3) {
                    DrawListSlotTiles(panel, entry->value, panel->screen, entry->y, entry->width, 1, 0xb);
                } else {
                    DrawListSlotTiles(panel, entry->value, panel->screen, entry->y, entry->width, baseTile + i * 0x18, 0xc);
                }
            }
        }
        for (i = depth - 1; i < 3; i++) {
            if ((saved[i] = panel->path[i]) != NULL) {
                int child = saved[i]->childRow;
                entry = &rows->entries[child];
                DrawListSlotTiles(panel, entry->value, panel->screen, entry->y, entry->width, baseTile + child * 0x18, 0xc);
            }
        }
        for (i = 0; i < nodes->count; i++) {
            node = nodes->nodes[i];
            if (parentRow == node->parentRow && row == node->childRow) {
                panel->path[depth - 1] = node;
                break;
            }
        }
        RebuildSlotChain_020c2e68(panel, depth, saved);
        for (level = 0; level < 3; level++) {
            int child;
            if (panel->path[level] == NULL) {
                for (i = 0; i < rows->count; i++) {
                    entry = &rows->entries[i];
                    if ((entry->y - 2) / 16 > level) {
                        if (panel->rowStates[i] == 3) {
                            tile = 1;
                        } else {
                            tile = baseTile + i * 0x18;
                        }
                        DrawListSlotTiles(panel, entry->value, panel->screen, entry->y, entry->width, tile, 0xb);
                    }
                }
                break;
            }
            child = panel->path[level]->childRow;
            entry = &rows->entries[child];
            palette = 9;
            if ((entry->y - 2) / 16 <= (rows->entries[panel->selectedIndex].y - 2) / 16 && panel->locked == 0) {
                palette = 10;
            }
            DrawListSlotTiles(panel, entry->value, panel->screen, entry->y, entry->width, baseTile + child * 0x18, palette);
        }
        if (panel->onChange != NULL) {
            panel->onChange();
        }
        RefreshListRowColors(panel);
        return TRUE;
    }
    return found;
}
