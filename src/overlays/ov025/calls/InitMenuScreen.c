#include "nitro/types.h"

typedef char *(*PathResolver)(int resourceId);

typedef struct ListViewConfig {
    PathResolver resolvePath;
    void (*onChange)(void);
    u32 data;
    BOOL asyncLoad;
    u32 field;
    u8 mode;
    u32 cellSet;
    int *highlightCell;
    int *cursorCell;
    int maxSlots;
    int normalSequence;
    int highlightSequence;
} ListViewConfig;

typedef struct ObjManagerConfig {
    u32 vramKey;
    u32 params[3];
} ObjManagerConfig;

typedef struct LayerParams {
    u32 values[2];
} LayerParams;

typedef struct LayerConfig {
    LayerParams *params;
    u32 values[3];
} LayerConfig;

extern ListViewConfig data_ov025_020b76f4;
extern ObjManagerConfig data_ov025_020b76c0;
extern LayerParams data_ov025_020b76a8;
extern LayerConfig data_ov025_020b76b0;
extern u32 data_ov025_020b7780;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern u32 func_ov001_0207b228(void (*callback)(void));
extern void SetupSubBgLayers(void);
extern void InitTileTableFrom(u32 layers, LayerConfig *config);
extern int InitializeResourceContainer(u32 container, int *extra);
extern unsigned int MakePrimaryVramKey(unsigned int slot);
extern unsigned int MakePrimaryVramKey_02071214(unsigned int slot);
extern void InitObjManagerAndMark(u32 obj, ObjManagerConfig *config);
extern void func_ov027_020b9098(u32 obj, unsigned int key);
extern void func_ov027_020b8fb8(u32 obj, unsigned int key, int count);
extern u32 func_ov001_02073060(void);
extern u32 func_ov027_020b9e10(u32 owner, int layerId);
extern u8 func_ov001_0207b654(void);
extern int *FindWidgetById(u32 obj, int id);
extern s32 GetClampedPaletteSlot(void);
extern void SetEntrySlotsVisible(u32 obj, int *entry, int visible);
extern void InitSlotListView(u32 list, ListViewConfig *config);
extern void *func_0202c4a0(unsigned int key, u32 heapId);
extern void LoadSubBgGraphics(u32 screen, void *archive);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void func_ov025_020b584c(u32 menu);
extern void *QueueFileLoadRequest(unsigned int key, int loadMode, void *callback, void *userData);
extern void LoadMenuWidgetResource(unsigned int resource);
extern u32 SetupMenuTextLayers(void);

void *InitMenuScreen(BOOL loadImmediately)
{
    ListViewConfig config = data_ov025_020b76f4;
    ObjManagerConfig objConfig = data_ov025_020b76c0;
    LayerParams layerParams = data_ov025_020b76a8;
    LayerConfig layerConfig = data_ov025_020b76b0;
    u32 menu;
    void *archive;

    menu = (u32)NNSi_FndGetCurrentRootHeap();
    data_ov025_020b7780 = menu;
    *(int *)(menu + 0x66d0) = -1;
    if (loadImmediately) {
        *(u8 *)(menu + 0x64e9) = 1;
    }
    func_ov001_0207b228(SetupSubBgLayers);
    SetupSubBgLayers();
    layerConfig.params = &layerParams;
    InitTileTableFrom(menu + 0x64c8, &layerConfig);
    *(int *)(menu + 0x64e4) = 1;
    InitializeResourceContainer(menu + 0x4c, NULL);
    objConfig.vramKey = MakePrimaryVramKey(0x69);
    InitObjManagerAndMark(menu + 0x4c, &objConfig);
    func_ov027_020b9098(menu + 0x4c, MakePrimaryVramKey_02071214(0xc));
    func_ov027_020b8fb8(menu + 0x4c, MakePrimaryVramKey(0x6b), 3);
    config.data = func_ov001_02073060();
    config.field = func_ov027_020b9e10(menu + 0x64c8, 0x1a);
    config.cellSet = menu + 0x4c;
    config.mode = func_ov001_0207b654();
    config.highlightCell = FindWidgetById(menu + 0x4c, 0x15);
    config.cursorCell = FindWidgetById(menu + 0x4c, 0x16);
    config.maxSlots = GetClampedPaletteSlot();
    config.normalSequence = 2;
    config.highlightSequence = 3;
    if (*(u8 *)(menu + 0x64e9) != 0) {
        config.asyncLoad = FALSE;
        SetEntrySlotsVisible(menu + 0x4c, config.highlightCell, TRUE);
    } else {
        SetEntrySlotsVisible(menu + 0x4c, config.highlightCell, FALSE);
    }
    SetEntrySlotsVisible(menu + 0x4c, FindWidgetById(menu + 0x4c, 3), FALSE);
    InitSlotListView(menu + 0x64f4, &config);
    if (*(u8 *)(menu + 0x64e9) != 0) {
        archive = func_0202c4a0(MakePrimaryVramKey_02071214(0xb), 14);
        LoadSubBgGraphics(menu, archive);
        NNSi_FndFreeFromDefaultHeap(archive);
        func_ov025_020b584c(menu);
    } else {
        QueueFileLoadRequest(MakePrimaryVramKey_02071214(0xb), 1, LoadMenuWidgetResource, NULL);
    }
    return SetupMenuTextLayers;
}
