#include "nitro/types.h"

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

typedef struct MenuFlags98 {
    u8 pad0_2 : 3;
    u8 loaded : 1;
    u8 objReady : 1;
    u8 active : 1;
    u8 pad6_7 : 2;
} MenuFlags98;

typedef struct MenuFlags99 {
    u8 visible : 1;
    u8 pad1 : 1;
    u8 ready : 1;
    u8 pad3_5 : 3;
    u8 busy : 1;
    u8 pad7 : 1;
} MenuFlags99;

typedef struct MenuFlagsD259 {
    u8 skipA : 1;
    u8 skipB : 1;
    u8 pad2_7 : 6;
} MenuFlagsD259;

typedef struct MenuState {
    u8 pad_00[0xa];
    u16 paletteWord;
    u16 paletteWordCopy;
    u8 pad_0e[0x98 - 0xe];
    MenuFlags98 flags98;
    MenuFlags99 flags99;
    u8 pad_9a[0x304 - 0x9a];
    u8 bgMain[0x98];
    u8 objMain[0x647c];
    u8 objSub[0x647c];
    u8 pad_cc94[0xd259 - 0xcc94];
    MenuFlagsD259 flagsD259;
} MenuState;

extern MenuState *data_ov013_02074ce0;
extern BgContainerConfig data_ov013_02074a08;
extern ObjManagerConfig data_ov013_02074a5c;
extern char sOv013_WxcWlaP2_02074c4c[];
extern u32 gPanelAssetPaths[];

extern void func_ov027_020b7e1c(void *container);
extern void DestroyObjectsAndRelease(void *container);
extern int Msg_OpenContainerAndReadHeader(const char *path, u32 kind, u32 fromTop);
extern void func_ov002_020629b8(void);
extern void GX_SetBankForOBJExtPltt(int bank);
extern void func_ov027_020b7d78(void *container, BgContainerConfig *config);
extern void func_ov027_020b7e44(void *container, u32 resourceId);
extern void *func_0202c4a0(u32 resourceId, u32 kind);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GX_LoadBGPltt(void *data, u32 offset, u32 size);
extern void GX_LoadBG1Char(void *data, u32 offset, u32 size);
extern void GX_LoadBG1Scr(void *data, u32 offset, u32 size);
extern void GX_LoadBG0Scr(void *data, u32 offset, u32 size);
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
extern void LoadAvatarObjPalette(BOOL useSubScreen);
extern void func_ov013_0207174c(int phase);
extern void GX_BeginLoadOBJExtPltt(void);
extern void GX_EndLoadOBJExtPltt(void);
extern void OpenPanelTextWindow(int a, int b);

void InitMenuScreenGraphics(void)
{
    BgContainerConfig bgConfig = data_ov013_02074a08;
    ObjManagerConfig objConfig = data_ov013_02074a5c;
    BgGraphicsData bgData;
    void *container;
    int handle;
    void *archive;
    u32 resourceBase;
    BgEntry *entry;

    if (data_ov013_02074ce0->flags98.loaded) {
        data_ov013_02074ce0->flags98.active = 0;
        data_ov013_02074ce0->flags99.visible = 0;
        func_ov027_020b7e1c(data_ov013_02074ce0->bgMain);
        DestroyObjectsAndRelease(data_ov013_02074ce0->objMain);
        data_ov013_02074ce0->flags98.objReady = 0;
        data_ov013_02074ce0->flags99.ready = 0;
        data_ov013_02074ce0->flags99.busy = 0;
    }
    data_ov013_02074ce0->flags98.loaded = 1;
    handle = Msg_OpenContainerAndReadHeader(sOv013_WxcWlaP2_02074c4c, 0x10, 0);
    func_ov002_020629b8();
    GX_SetBankForOBJExtPltt(0x20);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1e00;
    func_ov027_020b7d78(data_ov013_02074ce0->bgMain, &bgConfig);
    resourceBase = (handle + 0x8000U & 0xfffffc) << 7;
    func_ov027_020b7e44(data_ov013_02074ce0->bgMain, resourceBase | 0x80000000);
    archive = func_0202c4a0(resourceBase | 0x80000002, 0x10);
    GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
    GX_LoadBGPltt(bgData.palette->data, 0, bgData.palette->size);
    GX_LoadBG1Char(bgData.character->data, 0, bgData.character->size);
    entry = func_ov027_020b8578(data_ov013_02074ce0->bgMain, 0);
    GX_LoadBG1Scr(entry->screen->data, 0, entry->screen->size);
    entry = func_ov027_020b8578(data_ov013_02074ce0->bgMain, 1);
    GX_LoadBG0Scr(entry->screen->data, 0, entry->screen->size);
    *(vu16 *)0x04000008 = (u16)((*(vu16 *)0x04000008 & ~3) | 2);
    *(vu16 *)0x0400000a = (u16)((*(vu16 *)0x0400000a & ~3) | 3);
    *(vu16 *)0x0400000c = (u16)((*(vu16 *)0x0400000c & ~3) | 1);
    *(vu16 *)0x0400000e = (u16)(*(vu16 *)0x0400000e & ~3);
    objConfig.cellResourceId = resourceBase | 0x80000004;
    objConfig.animResourceId = resourceBase | 0x80000007;
    InitializeResourceContainer(data_ov013_02074ce0->objMain, NULL);
    InitObjManagerAndMark(data_ov013_02074ce0->objMain, &objConfig);
    func_ov027_020b9098(data_ov013_02074ce0->objMain, gPanelAssetPaths[2]);
    func_ov027_020b8fb8(data_ov013_02074ce0->objMain, objConfig.animResourceId, 0x19);
    data_ov013_02074ce0->flags98.objReady = 1;
    SetAllElementObjectModes(data_ov013_02074ce0->objMain, 3);
    NNSi_FndFreeFromDefaultHeap(archive);
    ZeroHalfThenFree(handle);

    container = data_ov013_02074ce0->objMain;
    SetEntrySlotsVisible(container, FindWidgetById(container, 0xb), 0);
    container = data_ov013_02074ce0->objMain;
    SetEntrySlotsVisible(container, FindWidgetById(container, 2), 0);
    container = data_ov013_02074ce0->objMain;
    SetEntrySlotsVisible(container, FindWidgetById(container, 3), 0);
    container = data_ov013_02074ce0->objMain;
    SetEntrySlotsVisible(container, FindWidgetById(container, 0xf), 1);
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b9604(container, FindWidgetById(container, 0x14));
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b9604(container, FindWidgetById(container, 0x15));
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b9604(container, FindWidgetById(container, 10));
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b97d8(container, FindWidgetById(container, 8), 0);
    LoadAvatarObjPalette(FALSE);
    if (!data_ov013_02074ce0->flagsD259.skipA && !data_ov013_02074ce0->flagsD259.skipB) {
        func_ov013_0207174c(1);
    }
    GX_BeginLoadOBJExtPltt();
    data_ov013_02074ce0->paletteWord = *(u16 *)0x06890002;
    data_ov013_02074ce0->paletteWordCopy = data_ov013_02074ce0->paletteWord;
    GX_EndLoadOBJExtPltt();
    OpenPanelTextWindow(0, 1);
    *(vu32 *)0x0400001c = 0x1ec0000;
    data_ov013_02074ce0->flags98.active = 1;
    data_ov013_02074ce0->flags99.visible = 1;
    data_ov013_02074ce0->flags99.ready = 1;
}
