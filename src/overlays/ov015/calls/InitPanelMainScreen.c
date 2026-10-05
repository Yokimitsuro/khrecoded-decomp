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

typedef struct PlayerCard {
    u8 pad_00[0x68];
    u8 avatarFrame;
    u8 pad_69[7];
} PlayerCard;

typedef struct ScreenFlagsE0 {
    u8 pad0_3 : 4;
    u8 subObjReady : 1;
    u8 mainObjReady : 1;
    u8 pad6_7 : 2;
} ScreenFlagsE0;

typedef struct ScreenFlagsE1 {
    u8 slotCleared : 3;
    u8 active : 1;
    u8 scrolling : 1;
    u8 mode : 2;
    u8 visible : 1;
} ScreenFlagsE1;

typedef struct ScreenFlagsE2 {
    u8 pad0 : 1;
    u8 ready : 1;
    u8 busy : 1;
    u8 pad3_7 : 5;
} ScreenFlagsE2;

typedef struct AvatarFlags {
    u8 layer : 2;
    u8 pad2_7 : 6;
} AvatarFlags;

typedef struct PanelContext {
    u8 pad_00[0xe0];
    ScreenFlagsE0 flagsE0;
    ScreenFlagsE1 flagsE1;
    ScreenFlagsE2 flagsE2;
    u8 pad_e3[0xec - 0xe3];
    s32 cardIndex;
    u8 pad_f0[0x100 - 0xf0];
    VecFx32 avatarPos;
    u8 pad_10c[0x118 - 0x10c];
    PlayerCard *avatarCard;
    u8 pad_11c[0x5aa - 0x11c];
    u8 avatarAlpha;
    AvatarFlags avatarFlags;
    u8 bgMain[0x98];
    u8 objMain[0xc914];
    PlayerCard cards[1];
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern BgContainerConfig data_ov015_02079ff0;
extern ObjManagerConfig data_ov015_0207a064;
extern char sOv015_WxcWleP2_0207e7f8[];
extern u32 gLinkPanelAssetPaths[];

extern void func_ov015_0206c670(void);
extern void GX_SetBankForOBJExtPltt(int bank);
extern void GX_SetBankForSubOBJExtPltt(int bank);
extern void *G2_GetBG0ScrPtr(void);
extern void MIi_CpuClear16(u32 value, void *dest, u32 size);
extern int Msg_OpenContainerAndReadHeader(const char *path, u32 kind, u32 fromTop);
extern void func_ov027_020b7d78(void *container, BgContainerConfig *config);
extern void func_ov027_020b7e44(void *container, u32 resourceId);
extern void *func_0202c4a0(u32 resourceId, u32 kind);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GX_LoadBGPltt(void *data, u32 offset, u32 size);
extern void GX_LoadBG1Char(void *data, u32 offset, u32 size);
extern void GX_LoadBG1Scr(void *data, u32 offset, u32 size);
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
extern void func_ov027_020b96c0(void *container, ObjElement *element, int frame);
extern void LoadAvatarObjPalette(BOOL useSubScreen);
extern void ResetSelectionView(VecFx32 *position);
extern void func_ov002_02067c10(void *container, VecFx32 *position);
extern void SetGroupSlotsVisible(void *container, VecFx32 *position, int value);

void InitPanelMainScreen(void)
{
    BgContainerConfig bgConfig = data_ov015_02079ff0;
    ObjManagerConfig objConfig = data_ov015_0207a064;
    BgGraphicsData bgData;
    PanelContext *ctx;
    void *container;
    int handle;
    void *archive;
    u32 resourceBase;
    BgEntry *entry;

    data_ov015_0207e960->flagsE1.active = 0;
    data_ov015_0207e960->flagsE2.ready = 0;
    data_ov015_0207e960->flagsE1.scrolling = 0;
    data_ov015_0207e960->flagsE1.visible = 0;
    data_ov015_0207e960->flagsE1.mode = 0;
    func_ov015_0206c670();
    data_ov015_0207e960->flagsE0.subObjReady = 1;
    GX_SetBankForOBJExtPltt(0x20);
    GX_SetBankForSubOBJExtPltt(0x100);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1e00;
    MIi_CpuClear16(0, G2_GetBG0ScrPtr(), 0x800);

    handle = Msg_OpenContainerAndReadHeader(sOv015_WxcWleP2_0207e7f8, 0x10, 0);
    func_ov027_020b7d78(data_ov015_0207e960->bgMain, &bgConfig);
    resourceBase = (handle + 0x8000U & 0xfffffc) << 7;
    func_ov027_020b7e44(data_ov015_0207e960->bgMain, resourceBase | 0x80000002);
    archive = func_0202c4a0(resourceBase | 0x80000004, 0x10);
    GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
    GX_LoadBGPltt(bgData.palette->data, 0, bgData.palette->size);
    GX_LoadBG1Char(bgData.character->data, 0, bgData.character->size);
    entry = func_ov027_020b8578(data_ov015_0207e960->bgMain, 0);
    GX_LoadBG1Scr(entry->screen->data, 0, entry->screen->size);
    objConfig.cellResourceId = resourceBase | 0x80000000;
    objConfig.animResourceId = resourceBase | 0x80000006;
    InitializeResourceContainer(data_ov015_0207e960->objMain, NULL);
    InitObjManagerAndMark(data_ov015_0207e960->objMain, &objConfig);
    func_ov027_020b9098(data_ov015_0207e960->objMain, gLinkPanelAssetPaths[2]);
    func_ov027_020b8fb8(data_ov015_0207e960->objMain, objConfig.animResourceId, 5);
    SetAllElementObjectModes(data_ov015_0207e960->objMain, 1);
    NNSi_FndFreeFromDefaultHeap(archive);
    ZeroHalfThenFree(handle);

    container = data_ov015_0207e960->objMain;
    SetEntrySlotsVisible(container, FindWidgetById(container, 0), 1);
    container = data_ov015_0207e960->objMain;
    SetEntrySlotsVisible(container, FindWidgetById(container, 1), 1);
    container = data_ov015_0207e960->objMain;
    func_ov027_020b9604(container, FindWidgetById(container, 0));
    container = data_ov015_0207e960->objMain;
    func_ov027_020b9604(container, FindWidgetById(container, 1));
    container = data_ov015_0207e960->objMain;
    func_ov027_020b96c0(container, FindWidgetById(container, 1), 6);
    ctx = data_ov015_0207e960;
    container = ctx->objMain;
    func_ov027_020b96c0(container, FindWidgetById(container, 0), ctx->cards[ctx->cardIndex].avatarFrame);
    LoadAvatarObjPalette(TRUE);
    ctx = data_ov015_0207e960;
    ctx->avatarCard = &ctx->cards[ctx->cardIndex];
    ResetSelectionView(&data_ov015_0207e960->avatarPos);
    data_ov015_0207e960->avatarAlpha = 200;
    data_ov015_0207e960->avatarFlags.layer = 1;
    data_ov015_0207e960->avatarPos.x = 0xc8000;
    data_ov015_0207e960->avatarPos.y = 0x32000;
    ctx = data_ov015_0207e960;
    func_ov002_02067c10(ctx->objMain, &ctx->avatarPos);
    ctx = data_ov015_0207e960;
    SetGroupSlotsVisible(ctx->objMain, &ctx->avatarPos, 1);
    data_ov015_0207e960->flagsE1.active = 1;
    data_ov015_0207e960->flagsE2.ready = 1;
    data_ov015_0207e960->flagsE2.busy = 0;
}
