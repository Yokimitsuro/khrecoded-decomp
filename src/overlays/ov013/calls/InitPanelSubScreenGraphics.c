#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct BgContainerConfig {
    u32 values[5];
} BgContainerConfig;

typedef struct ObjManagerConfig {
    u32 cellResourceId;
    u32 pad_04[4];
    u32 animResourceId;
} ObjManagerConfig;

typedef struct PaletteData {
    u32 format;
    BOOL isExtended;
    u32 size;
    void *data;
} PaletteData;

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
    void *data;
} CharacterData;

typedef struct BgGraphicsData {
    void *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

typedef struct ScreenData {
    u8 pad_00[8];
    u32 size;
    u8 data[4];
} ScreenData;

typedef struct BgEntry {
    u8 pad_00[8];
    ScreenData *screen;
} BgEntry;

typedef struct ObjElement {
    u8 pad_00[0x14];
    s32 animIndex;
} ObjElement;

typedef struct PanelPoint {
    fx32 x;
    fx32 y;
} PanelPoint;

typedef struct PanelState {
    u8 pad_00[2];
    s8 hiddenCount;
    u8 pad_03;
    s8 rowHeight;
    s8 iconRowHeight;
    u8 pad_06[0x9c - 0x6];
    PanelPoint slotPoints[5][9];
    u8 pad_204[0x350 - 0x204];
    u8 bgSub[0x6818 - 0x350];
    u8 objSub[0xd150 - 0x6818];
    ObjElement *frameObjects[9];
    ObjElement *iconObjects[9];
    ObjElement *digitObjects[27];
    ObjElement *extraObjects[21];
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern BgContainerConfig data_ov013_02074a1c;
extern ObjManagerConfig data_ov013_02074a8c;
extern char sOv013_WxcWlaP2_02074c4c[];
extern u32 gPanelAssetPaths[];

extern int Msg_OpenContainerAndReadHeader(const char *path, u32 kind, u32 fromTop);
extern void GX_SetBankForSubOBJExtPltt(int bank);
extern void func_ov027_020b7d78(void *container, BgContainerConfig *config);
extern void func_ov027_020b7e44(void *container, u32 resourceId);
extern void *func_0202c4a0(u32 resourceId, u32 kind);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GXS_LoadBGPltt(void *data, u32 offset, u32 size);
extern void GXS_LoadBG0Char(void *data, u32 offset, u32 size);
extern void GXS_LoadBG1Scr(void *data, u32 offset, u32 size);
extern void GXS_LoadBG0Scr(void *data, u32 offset, u32 size);
extern void func_ov013_02070b78(s32 param1, s32 param2);
extern BgEntry *func_ov027_020b8578(void *container, int entryId);
extern void InitializeResourceContainer(void *container, ObjManagerConfig *config);
extern void InitObjManagerAndMark(void *container, ObjManagerConfig *config);
extern void func_ov027_020b9098(void *container, u32 value);
extern void func_ov027_020b8fb8(void *container, u32 resourceId, int count);
extern void SetAllElementObjectModes(void *container, int mode);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void ZeroHalfThenFree(int handle);
extern ObjElement *FindWidgetById(void *container, int elementId);
extern void SetEntrySlotsVisible(void *container, ObjElement *element, BOOL visible);
extern void func_ov027_020b9604(void *container, ObjElement *element);
extern void func_ov027_020b97d8(void *container, ObjElement *element, int mode);
extern void ApplySelectedSubitemValues(void *container, ObjElement *element, int useAlt);
extern fx32 *func_ov027_020b9380(void *container, ObjElement *element, PanelPoint *position, int mode);
extern void SetFocusedWidget(void *container, ObjElement *element);
extern void func_ov027_020b90a8(void *container, int elementId, void (*callback)(void));
extern void func_0204f18c(void *container, s32 animIndex, int value);
extern void func_ov013_02074598(void);
extern void func_ov013_020745a8(void);
extern void func_ov013_02074658(void);
extern void CheckClearCountMilestone(void);
extern void SelectPanelResultMode1(void);
extern void SelectPanelResultMode2(void);
extern void func_ov013_02074718(void);
extern void SelectPanelTint0(void);
extern void SelectPanelTint1(void);
extern void SelectPanelTint2(void);
extern void SelectPanelTint3(void);
extern void SelectPanelTint4(void);
extern void SelectPanelTint5(void);
extern void func_ov013_020749ec(void);
extern void func_ov013_020749f0(void);

void InitPanelSubScreenGraphics(void)
{
    BgContainerConfig bgConfig = data_ov013_02074a1c;
    ObjManagerConfig objConfig = data_ov013_02074a8c;
    BgGraphicsData bgData;
    int i;
    void *container;
    int handle;
    void *archive;
    u32 resourceBase;
    BgEntry *entry;
    ObjElement *object;

    handle = Msg_OpenContainerAndReadHeader(sOv013_WxcWlaP2_02074c4c, 0x10, 0);
    GX_SetBankForSubOBJExtPltt(0);
    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1f00;
    func_ov027_020b7d78(data_ov013_02074ce0->bgSub, &bgConfig);
    resourceBase = (handle + 0x8000U & 0xfffffc) << 7;
    func_ov027_020b7e44(data_ov013_02074ce0->bgSub, resourceBase | 0x80000001);
    archive = func_0202c4a0(resourceBase | 0x80000003, 0x10);
    GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
    GXS_LoadBGPltt(bgData.palette->data, 0, bgData.palette->size);
    GXS_LoadBG0Char(bgData.character->data, 0, bgData.character->size);
    NNSi_FndFreeFromDefaultHeap(archive);
    archive = func_0202c4a0(gPanelAssetPaths[0], 0x10);
    GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
    GXS_LoadBG0Char(bgData.character->data, 0xc000, bgData.character->size);
    NNSi_FndFreeFromDefaultHeap(archive);
    func_ov013_02070b78(1, data_ov013_02074ce0->hiddenCount);
    entry = func_ov027_020b8578(data_ov013_02074ce0->bgSub, 0);
    GXS_LoadBG1Scr(entry->screen->data, 0, entry->screen->size);
    entry = func_ov027_020b8578(data_ov013_02074ce0->bgSub, 3);
    GXS_LoadBG0Scr(entry->screen->data, 0, entry->screen->size);
    objConfig.cellResourceId = resourceBase | 0x80000005;
    objConfig.animResourceId = resourceBase | 0x80000006;
    InitializeResourceContainer(data_ov013_02074ce0->objSub, NULL);
    InitObjManagerAndMark(data_ov013_02074ce0->objSub, &objConfig);
    func_ov027_020b9098(data_ov013_02074ce0->objSub, gPanelAssetPaths[4]);
    func_ov027_020b8fb8(data_ov013_02074ce0->objSub, objConfig.animResourceId, 0x5c);
    SetAllElementObjectModes(data_ov013_02074ce0->objSub, 3);

    container = data_ov013_02074ce0->objSub;
    func_ov027_020b97d8(container, FindWidgetById(container, 9), 1);
    container = data_ov013_02074ce0->objSub;
    func_ov027_020b97d8(container, FindWidgetById(container, 10), 1);
    container = data_ov013_02074ce0->objSub;
    func_ov027_020b97d8(container, FindWidgetById(container, 5), 1);
    container = data_ov013_02074ce0->objSub;
    func_0204f18c(container, FindWidgetById(container, 6)->animIndex, 0);
    container = data_ov013_02074ce0->objSub;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 5), 0);
    container = data_ov013_02074ce0->objSub;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 6), 0);
    ZeroHalfThenFree(handle);

    for (i = 0; i < 9; i++) {
        data_ov013_02074ce0->frameObjects[i] = FindWidgetById(data_ov013_02074ce0->objSub, i + 0x13);
    }
    for (i = 0; i < 9; i++) {
        data_ov013_02074ce0->iconObjects[i] = FindWidgetById(data_ov013_02074ce0->objSub, i + 0x1d);
    }
    for (i = 0; i < 27; i++) {
        data_ov013_02074ce0->digitObjects[i] = FindWidgetById(data_ov013_02074ce0->objSub, i + 0x28);
    }
    for (i = 0; i < 21; i++) {
        data_ov013_02074ce0->extraObjects[i] = FindWidgetById(data_ov013_02074ce0->objSub, i + 300);
    }

    container = data_ov013_02074ce0->objSub;
    SetEntrySlotsVisible(container, FindWidgetById(container, 9), 0);
    container = data_ov013_02074ce0->objSub;
    SetEntrySlotsVisible(container, FindWidgetById(container, 10), 0);
    SetEntrySlotsVisible(data_ov013_02074ce0->objSub, data_ov013_02074ce0->iconObjects[0], 0);
    SetEntrySlotsVisible(data_ov013_02074ce0->objSub, data_ov013_02074ce0->frameObjects[0], 0);
    if (data_ov013_02074ce0->hiddenCount < 9) {
        for (i = 0; i < 9 - data_ov013_02074ce0->hiddenCount; i++) {
            container = data_ov013_02074ce0->objSub;
            SetEntrySlotsVisible(container, FindWidgetById(container, 0x25 - i), 0);
            container = data_ov013_02074ce0->objSub;
            SetEntrySlotsVisible(container, FindWidgetById(container, 0x1b - i), 0);
        }
    }
    container = data_ov013_02074ce0->objSub;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 0x25), 0);
    container = data_ov013_02074ce0->objSub;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 0x1b), 0);

    for (i = 0; i < 9; i++) {
        func_ov027_020b9604(data_ov013_02074ce0->objSub, data_ov013_02074ce0->iconObjects[i]);
        container = data_ov013_02074ce0->objSub;
        func_ov027_020b9604(container, FindWidgetById(container, i + 200));
        func_ov027_020b9604(data_ov013_02074ce0->objSub, data_ov013_02074ce0->digitObjects[i * 3 + 0]);
        func_ov027_020b9604(data_ov013_02074ce0->objSub, data_ov013_02074ce0->digitObjects[i * 3 + 1]);
        func_ov027_020b9604(data_ov013_02074ce0->objSub, data_ov013_02074ce0->digitObjects[i * 3 + 2]);
        func_ov027_020b97d8(data_ov013_02074ce0->objSub, data_ov013_02074ce0->digitObjects[i * 3 + 0], 3);
        func_ov027_020b97d8(data_ov013_02074ce0->objSub, data_ov013_02074ce0->digitObjects[i * 3 + 1], 3);
        func_ov027_020b97d8(data_ov013_02074ce0->objSub, data_ov013_02074ce0->digitObjects[i * 3 + 2], 3);
    }
    for (i = 0; i < 9; i++) {
        func_ov027_020b9380(data_ov013_02074ce0->objSub, data_ov013_02074ce0->frameObjects[i],
                            &data_ov013_02074ce0->slotPoints[0][i], 0);
        func_ov027_020b9380(data_ov013_02074ce0->objSub, data_ov013_02074ce0->iconObjects[i],
                            &data_ov013_02074ce0->slotPoints[1][i], 0);
        func_ov027_020b9380(data_ov013_02074ce0->objSub, data_ov013_02074ce0->digitObjects[i * 3],
                            &data_ov013_02074ce0->slotPoints[2][i], 0);
        object = FindWidgetById(data_ov013_02074ce0->objSub, i + 200);
        func_ov027_020b9380(data_ov013_02074ce0->objSub, object, &data_ov013_02074ce0->slotPoints[3][i], 0);
        object = FindWidgetById(data_ov013_02074ce0->objSub, i + 100);
        func_ov027_020b9380(data_ov013_02074ce0->objSub, object, &data_ov013_02074ce0->slotPoints[4][i], 0);
    }
    data_ov013_02074ce0->rowHeight =
        (data_ov013_02074ce0->slotPoints[0][1].y - data_ov013_02074ce0->slotPoints[0][0].y) >> 12;
    data_ov013_02074ce0->iconRowHeight =
        (data_ov013_02074ce0->slotPoints[1][1].y - data_ov013_02074ce0->slotPoints[1][0].y) >> 12;
    SetFocusedWidget(data_ov013_02074ce0->objSub, FindWidgetById(data_ov013_02074ce0->objSub, 0x14));
    func_ov027_020b97d8(data_ov013_02074ce0->objSub, FindWidgetById(data_ov013_02074ce0->objSub, 2), 0);
    func_ov027_020b97d8(data_ov013_02074ce0->objSub, FindWidgetById(data_ov013_02074ce0->objSub, 3), 0);
    func_ov027_020b90a8(data_ov013_02074ce0->objSub, 2, func_ov013_02074598);
    func_ov027_020b90a8(data_ov013_02074ce0->objSub, 3, func_ov013_020745a8);
    func_ov027_020b90a8(data_ov013_02074ce0->objSub, 5, func_ov013_02074658);
    func_ov027_020b90a8(data_ov013_02074ce0->objSub, 6, CheckClearCountMilestone);
    func_ov027_020b90a8(data_ov013_02074ce0->objSub, 9, SelectPanelResultMode1);
    func_ov027_020b90a8(data_ov013_02074ce0->objSub, 10, SelectPanelResultMode2);
    func_ov027_020b90a8(data_ov013_02074ce0->objSub, 0x13, func_ov013_02074718);
    func_ov027_020b90a8(data_ov013_02074ce0->objSub, 0x14, SelectPanelTint0);
    func_ov027_020b90a8(data_ov013_02074ce0->objSub, 0x15, SelectPanelTint1);
    func_ov027_020b90a8(data_ov013_02074ce0->objSub, 0x16, SelectPanelTint2);
    func_ov027_020b90a8(data_ov013_02074ce0->objSub, 0x17, SelectPanelTint3);
    func_ov027_020b90a8(data_ov013_02074ce0->objSub, 0x18, SelectPanelTint4);
    func_ov027_020b90a8(data_ov013_02074ce0->objSub, 0x19, SelectPanelTint5);
    func_ov027_020b90a8(data_ov013_02074ce0->objSub, 0x1a, func_ov013_020749ec);
    func_ov027_020b90a8(data_ov013_02074ce0->objSub, 0x1b, func_ov013_020749f0);
}
