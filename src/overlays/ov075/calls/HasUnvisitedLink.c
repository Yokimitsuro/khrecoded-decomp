#include "nitro/types.h"

typedef struct LinkEntry {
    u8 pad_00[2];
    u8 kind;
    u8 pad_03[3];
    u16 flagIndex;
} LinkEntry;

typedef struct GridLayout {
    u8 pad_00[0x9c];
    LinkEntry *entries[1];
} GridLayout;

typedef struct MatrixNode {
    u8 pad_00[0xc];
    s16 links[4];
} MatrixNode;

typedef struct MatrixMenu {
    u8 pad_00000[0x12dd0];
    GridLayout *layout;
    MatrixNode *current;
    u8 visited[1];
} MatrixMenu;

BOOL HasUnvisitedLink(MatrixMenu *menu)
{
    s16 *link;
    LinkEntry *entry = NULL;
    int i;

    link = menu->current->links;

    for (i = 0; i < 4; i++, link++) {
        if (*link >= 0) {
            entry = menu->layout->entries[*link];
            if (entry->kind == 1) {
                break;
            }
        }
    }
    if (i < 4 && menu->visited[entry->flagIndex] == 0) {
        return TRUE;
    }
    return FALSE;
}