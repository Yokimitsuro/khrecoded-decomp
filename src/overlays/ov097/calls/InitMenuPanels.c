#include "nitro/types.h"

typedef struct {
    u8 data[0x6434];
} PanelList;

typedef struct {
    u8 data[0x1c];
} PanelSlotDef;

typedef struct {
    u32 fileId;
    int layerCount;
    int unk_08;
    int unk_0c;
} ObjManagerConfig;

typedef struct {
    u8 pad_0000[0x18];
    int fileBase;
    u8 pad_001c[4];
    int cellFileBase;
    u8 pad_0024[0x218 - 0x24];
    PanelList panelLists[2];
} MenuScene;

extern PanelSlotDef data_ov097_020c2010[];
extern PanelSlotDef data_ov097_020c22e4[];
extern void InitObjManager(PanelList *manager, ObjManagerConfig *config);
extern void PXI_Init_0204f020(PanelList *manager, u32 fileId);
extern void BindPanelSlot(int listIndex, int slotIndex, PanelSlotDef *def, MenuScene *scene);
extern BOOL IsEntryFlagSet_020c1494(int flagSet, int entryIndex);
extern void SetPanelSlotFlag(int listIndex, int slotIndex, BOOL enabled, MenuScene *scene);
extern void TickPanelSlotAnimation(int listIndex, int slotIndex, int frames, MenuScene *scene);

#define MENU_FILE_ID(base, index) ((((base) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

void InitMenuPanels(MenuScene *scene)
{
    ObjManagerConfig config;
    BOOL unlocked;
    int frames;
    int i;

    config.fileId = MENU_FILE_ID(scene->fileBase, 10);
    config.layerCount = 2;
    config.unk_08 = 0;
    config.unk_0c = 0;
    InitObjManager(&scene->panelLists[0], &config);
    PXI_Init_0204f020(&scene->panelLists[0], MENU_FILE_ID(scene->cellFileBase, 0));
    for (i = 0; i < 11; i++) {
        BindPanelSlot(0, i, &data_ov097_020c2010[i], scene);
    }
    for (i = 0; i < 8; i++) {
        unlocked = IsEntryFlagSet_020c1494(1, i);
        frames = IsEntryFlagSet_020c1494(2, i) != FALSE;
        SetPanelSlotFlag(0, i + 3, unlocked, scene);
        TickPanelSlotAnimation(0, i + 3, frames, scene);
    }
    config.fileId = MENU_FILE_ID(scene->fileBase, 8);
    config.layerCount = 1;
    config.unk_08 = 0;
    config.unk_0c = 0;
    InitObjManager(&scene->panelLists[1], &config);
    for (i = 0; i < 20; i++) {
        BindPanelSlot(1, i, &data_ov097_020c22e4[i], scene);
    }
}
