#include "nitro/types.h"

typedef struct MenuItem {
    u8 kind;
    u8 panelCount;
} MenuItem;

typedef struct MenuItemTable {
    u8 pad_00[8];
    MenuItem *items[1];
} MenuItemTable;

typedef struct {
    s8 state;
    u8 pad_01[0xf];
} SceneSlot;

typedef struct MenuScene {
    MenuItemTable *table;
    u8 pad_04[8];
    s8 mode;
    s8 selected;
    u8 pad_0e[6];
    u8 *panels;
    u8 pad_18[0x1098 - 0x18];
    SceneSlot slots[2];
    u8 loadState;
} MenuScene;

extern MenuScene *data_ov001_020a048c;

extern BOOL FinishSceneSlotLoad(SceneSlot *slot, MenuScene *scene);
extern BOOL LoadNextSceneSlotResources(SceneSlot *slot, MenuItem *item, MenuScene *scene);
extern void SyncDoorMeshState(u8 *panel, int index);

BOOL UpdateMenuItemLoading(void) {
    MenuScene *scene = data_ov001_020a048c;
    BOOL done = TRUE;
    MenuItem *item;
    int i;

    if (scene->loadState != 1) {
        return done;
    }
    item = scene->table->items[scene->selected];
    for (i = 0; i < 2; i++) {
        SceneSlot *slot = &scene->slots[i];
        if (slot->state == 1 && FinishSceneSlotLoad(slot, scene)) {
            done = FALSE;
        }
        if (slot->state == 0 && LoadNextSceneSlotResources(slot, item, scene)) {
            done = FALSE;
        }
    }
    if (!done) {
        return FALSE;
    }
    for (i = 0; i < item->panelCount; i++) {
        SyncDoorMeshState(scene->panels + i * 0x24, i);
    }
    scene->loadState = 2;
    return TRUE;
}
