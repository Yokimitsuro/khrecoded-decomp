#include "nitro/types.h"

typedef struct {
    int archive;
    void *archiveTable;
    void *objectManager;
    int fontId;
} PopupManagerParams;

typedef struct {
    int currentEntry;
    int archives[2];
    u8 pad_0c[4];
    u8 archiveTable[0x6528 - 0x10];
    u8 objectManager[0xc9d4 - 0x6528];
    int fontId;
    u8 pad_c9d8[0xc9f4 - 0xc9d8];
    int values[5];
    void *popupManager;
    u8 pad_ca0c[0xcc00 - 0xca0c];
    int savedEntry;
    u8 pad_cc04[0xcc68 - 0xcc04];
    int mode;
    int modeStep;
    int modeTimer;
    u8 pad_cc74[0xcc7c - 0xcc74];
    BOOL altLayout;
} MenuScene;

extern MenuScene *data_ov091_020c3740;
extern const u8 data_ov091_020c2a50[];
extern void SetStateFlagBits(u8 clearMask, u8 setBits);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern int func_ov039_020bc848(void);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void AcquireMapLayout(int a, int b);
extern void SetupRecordMenuDisplay(MenuScene *scene);
extern void func_ov091_020bf1b4(MenuScene *scene);
extern void LoadMenuGraphics(MenuScene *scene);
extern void InitMenuTextLayers(MenuScene *scene);
extern void func_ov091_020bf7a8(MenuScene *scene);
extern void InitScrollList_020bfc8c(const void *layout, MenuScene *scene);
extern void *func_ov091_020c27bc(PopupManagerParams *params);
extern void func_ov091_020c0468(MenuScene *scene);
extern void func_ov091_020c114c(MenuScene *scene);
extern void func_ov091_020c12d4(MenuScene *scene);
extern void func_ov091_020c1370(MenuScene *scene);
extern void SyncRecordFlags(MenuScene *scene);
extern BOOL IsEntryFlagSet(int flagSet, int entryIndex);
extern void SetEntryFlag(int flagSet, int entryIndex);
extern void SetListPanelSlotFlag(int screen, int panelIndex, int value, MenuScene *scene);
extern void SetListPanelSlotValue(int screen, int panelIndex, BOOL value, MenuScene *scene);
extern void SetSceneMode(int mode, MenuScene *scene);

BOOL InitRecordMenuScene(MenuScene *scene)
{
    PopupManagerParams params;
    int i;
    int entry;

    data_ov091_020c3740 = scene;
    SetStateFlagBits(5, 0);
    MIi_CpuClearFast(0, scene, sizeof(MenuScene));
    scene->currentEntry = func_ov039_020bc848();
    scene->mode = 0;
    scene->modeStep = 0;
    scene->modeTimer = 0;
    scene->altLayout = FALSE;
    if (IsGlobalPackedBitSet(0xbea) && !IsGlobalPackedBitSet(0xf4c)) {
        scene->altLayout = TRUE;
    }
    for (i = 0; i < 5; i++) {
        scene->values[i] = 0;
    }
    AcquireMapLayout(0, 0);
    SetupRecordMenuDisplay(scene);
    func_ov091_020bf1b4(scene);
    LoadMenuGraphics(scene);
    InitMenuTextLayers(scene);
    func_ov091_020bf7a8(scene);
    InitScrollList_020bfc8c(data_ov091_020c2a50, scene);
    scene->currentEntry = func_ov039_020bc848();
    scene->savedEntry = scene->currentEntry;
    params.archive = scene->archives[0];
    params.archiveTable = scene->archiveTable;
    params.objectManager = scene->objectManager;
    params.fontId = scene->fontId;
    scene->popupManager = func_ov091_020c27bc(&params);
    func_ov091_020c0468(scene);
    func_ov091_020c114c(scene);
    func_ov091_020c12d4(scene);
    func_ov091_020c1370(scene);
    SyncRecordFlags(scene);
    for (i = 0; i < 5; i++) {
        SetListPanelSlotFlag(0, i + 1, IsEntryFlagSet(2, i), scene);
    }
    entry = scene->currentEntry;
    if (IsEntryFlagSet(2, entry)) {
        SetEntryFlag(3, entry);
    }
    entry = scene->currentEntry;
    SetListPanelSlotValue(0, entry + 1, IsEntryFlagSet(3, entry) != FALSE, scene);
    SetSceneMode(1, scene);
    return TRUE;
}
