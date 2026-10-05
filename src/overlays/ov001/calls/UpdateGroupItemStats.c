#include "nitro/types.h"

typedef struct Item {
    u8 id;
    u8 value;
    u8 level;
    u8 slot;
    u8 pad[4];
} Item;

typedef struct Group {
    u8 kind;
    u8 count;
    u8 pad[0x1e];
    Item *items;
} Group;

typedef struct GroupTable {
    u8 groupCount;
    u8 pad[7];
    Group *groups[1];
} GroupTable;

typedef struct GroupMenu {
    GroupTable *table;
    u8 pad_04[9];
    s8 currentGroup;
    u8 pad_0e;
    u8 menuFlags;
    u8 pad_10[4];
    u8 *panels;
} GroupMenu;

extern GroupMenu *data_ov001_020a048c;
extern void func_ov001_02066ef8(Item *item, int index);
extern Item *FindGroupItemById(u32 id, int groupIndex);
extern void SyncDoorMeshState(u8 *panel, int index);
extern void SetPanelItemHighlight(int index, BOOL highlighted);

void UpdateGroupItemStats(u32 id, int level, int value)
{
    GroupMenu *menu = data_ov001_020a048c;
    int groupCount = menu->table->groupCount;
    int g;

    for (g = 0; g < groupCount; g++) {
        Group *group = data_ov001_020a048c->table->groups[g];
        int i;
        for (i = 0; i < group->count; i++) {
            Item *entry = &group->items[i];
            u8 *panel = menu->panels + i * 0x24;
            if (entry->id == id) {
                Item *item = FindGroupItemById(id, g);
                if (level >= 0) {
                    item->level = level;
                }
                if (value >= 0) {
                    item->value = value;
                }
                if (g == data_ov001_020a048c->currentGroup) {
                    func_ov001_02066ef8(entry, i);
                    SyncDoorMeshState(panel, id);
                    if (data_ov001_020a048c->menuFlags & 1) {
                        SetPanelItemHighlight(entry->slot - 1, *(u16 *)(panel + 0x22) & 2);
                    }
                }
            }
        }
    }
}
