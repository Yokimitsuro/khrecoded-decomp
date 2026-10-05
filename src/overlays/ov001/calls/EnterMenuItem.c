#include "nitro/types.h"

typedef struct MenuItem {
    u8 kind;
    u8 panelCount;
    u8 pad_02[4];
    s8 flagIndex;
    u8 pad_07[0x20 - 0x07];
    u8 *panelDefs;
} MenuItem;

typedef struct MenuItemTable {
    u8 pad_00[8];
    MenuItem *items[1];
} MenuItemTable;

typedef struct MenuScene {
    MenuItemTable *table;
    u8 pad_04[8];
    s8 mode;
    s8 selected;
    u8 pad_0e[6];
    void *panels;
    u8 pad_18[0x10c1 - 0x18];
    u8 needsRedraw;
    u8 pad_10c2[0x10c8 - 0x10c2];
    u32 timer;
    u32 cursor;
    u32 scroll;
    u8 history[0x20];
} MenuScene;

extern MenuScene *data_ov001_020a048c;
extern u8 *data_0205fe0c;

extern void MI_CpuFill8(void *dst, u8 val, u32 size);
extern void MIi_CpuClearFast(u32 data, void *dst, u32 size);
extern void func_ov001_020645dc(u32 flag);
extern void InitLayerSlotsFromData(void);
extern void func_ov001_0206703c(void);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void func_ov001_02066ef8(u8 *def, int index);
extern void UpdatePointTriggerBox(u8 *def, int index);

void EnterMenuItem(int index) {
    int i;
    MenuScene *scene = data_ov001_020a048c;
    MenuItem *item = scene->table->items[index];
    s8 selected = index;

    data_0205fe0c[0x28d5] = selected;
    scene->selected = selected;
    scene->cursor = 0;
    scene->scroll = 0;
    MI_CpuFill8(scene->history, 0, sizeof(scene->history));
    scene->needsRedraw = 1;
    scene->timer = 0;
    if (item->flagIndex >= 0) {
        func_ov001_020645dc(item->flagIndex + 0x10d0);
    }
    InitLayerSlotsFromData();
    func_ov001_0206703c();
    scene->panels = NNSi_FndAllocFromDefaultHeap(item->panelCount * 0x24);
    MIi_CpuClearFast(0, scene->panels, item->panelCount * 0x24);
    for (i = 0; i < item->panelCount; i++) {
        func_ov001_02066ef8(item->panelDefs + i * 8, i);
        UpdatePointTriggerBox(item->panelDefs + i * 8, i);
    }
}
