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

typedef struct CardHeader {
    u32 words[4];
} CardHeader;

typedef struct PlayerCard {
    CardHeader header;
    u8 pad_10[0x58];
    u8 avatarFrame;
    u8 pad_69[7];
} PlayerCard;

typedef struct AvatarFlags {
    u8 layer : 2;
    u8 pad2_7 : 6;
} AvatarFlags;

typedef struct AvatarView {
    VecFx32 pos;
    u8 pad_0c[0x18 - 0xc];
    CardHeader *card;
    u8 pad_1c[0x4aa - 0x1c];
    u8 alpha;
    AvatarFlags flags;
} AvatarView;

typedef struct MenuFlags98 {
    u8 pad0_2 : 3;
    u8 loaded : 1;
    u8 objReady : 1;
    u8 active : 1;
    u8 pad6_7 : 2;
} MenuFlags98;

typedef struct MenuFlags99 {
    u8 visible : 1;
    u8 pad1_7 : 7;
} MenuFlags99;

typedef struct MenuState {
    u8 pad_00[0x98];
    MenuFlags98 flags98;
    MenuFlags99 flags99;
    u8 pad_9a[0x304 - 0x9a];
    u8 bgMain[0x98];
    u8 objMain[0xcc94 - 0x39c];
    AvatarView view;
    CardHeader savedCard;
} MenuState;

extern MenuState *data_ov013_02074ce0;
extern BgContainerConfig data_ov013_02074a30;
extern ObjManagerConfig data_ov013_02074a44;
extern char sOv013_WxcWlfP2_02074c58[];
extern u32 gPanelAssetPaths[];
extern int data_0206085c;

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
extern void func_ov027_020b97d8(void *container, ObjElement *element, int mode);
extern int func_ov013_02070cb4(void);
extern int DispatchContextCommand(u32 command, int value, int extra, void *buffer);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void LoadAvatarObjPalette(BOOL useSubScreen);
extern void ResetSelectionView(AvatarView *view);
extern void func_ov002_02067c10(void *container, AvatarView *view);
extern void SetGroupSlotsVisible(void *container, AvatarView *view, int value);
extern void OpenPanelTextWindow(int a, int b);

void InitRecordScreenGraphics(void)
{
    BgContainerConfig bgConfig = data_ov013_02074a30;
    ObjManagerConfig objConfig = data_ov013_02074a44;
    PlayerCard card;
    BgGraphicsData bgData;
    int i;
    MenuState *ctx;
    void *container;
    int handle;
    void *archive;
    u32 resourceBase;
    BgEntry *entry;
    int value;
    int digit;

    if (data_ov013_02074ce0->flags98.loaded) {
        data_ov013_02074ce0->flags98.active = 0;
        data_ov013_02074ce0->flags99.visible = 0;
        func_ov027_020b7e1c(data_ov013_02074ce0->bgMain);
        DestroyObjectsAndRelease(data_ov013_02074ce0->objMain);
        data_ov013_02074ce0->flags98.objReady = 0;
    }
    data_ov013_02074ce0->flags98.loaded = 1;
    handle = Msg_OpenContainerAndReadHeader(sOv013_WxcWlfP2_02074c58, 0x10, 0);
    func_ov002_020629b8();
    GX_SetBankForOBJExtPltt(0x20);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1e00;
    func_ov027_020b7d78(data_ov013_02074ce0->bgMain, &bgConfig);
    resourceBase = (handle + 0x8000U & 0xfffffc) << 7;
    func_ov027_020b7e44(data_ov013_02074ce0->bgMain, resourceBase | 0x80000000);
    archive = func_0202c4a0(resourceBase | 0x80000001, 0x10);
    GetBgDataFromArchive(&bgData, archive, -1, 0, 0);
    GX_LoadBGPltt(bgData.palette->data, 0, bgData.palette->size);
    GX_LoadBG1Char(bgData.character->data, 0, bgData.character->size);
    entry = func_ov027_020b8578(data_ov013_02074ce0->bgMain, 0);
    GX_LoadBG1Scr(entry->screen->data, 0, entry->screen->size);
    objConfig.cellResourceId = resourceBase | 0x80000002;
    objConfig.animResourceId = resourceBase | 0x80000003;
    InitializeResourceContainer(data_ov013_02074ce0->objMain, NULL);
    InitObjManagerAndMark(data_ov013_02074ce0->objMain, &objConfig);
    func_ov027_020b9098(data_ov013_02074ce0->objMain, gPanelAssetPaths[1]);
    func_ov027_020b8fb8(data_ov013_02074ce0->objMain, objConfig.animResourceId, 0xd);
    data_ov013_02074ce0->flags98.objReady = 1;
    SetAllElementObjectModes(data_ov013_02074ce0->objMain, 1);
    NNSi_FndFreeFromDefaultHeap(archive);
    ZeroHalfThenFree(handle);

    for (i = 0; i < 7; i++) {
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b9604(container, FindWidgetById(container, i + 10));
        container = data_ov013_02074ce0->objMain;
        SetEntrySlotsVisible(container, FindWidgetById(container, i + 10), 0);
    }
    func_ov027_020b97d8(data_ov013_02074ce0->objMain, FindWidgetById(data_ov013_02074ce0->objMain, 4), 0);
    DispatchContextCommand(0, func_ov013_02070cb4(), 0, &card);
    container = data_ov013_02074ce0->objMain;
    SetEntrySlotsVisible(container, FindWidgetById(container, 5), 1);
    container = data_ov013_02074ce0->objMain;
    func_ov027_020b9604(container, FindWidgetById(container, 5));
    func_ov027_020b96c0(data_ov013_02074ce0->objMain, FindWidgetById(data_ov013_02074ce0->objMain, 5),
                        card.avatarFrame);
    container = data_ov013_02074ce0->objMain;
    SetEntrySlotsVisible(container, FindWidgetById(container, 6), 1);
    container = data_ov013_02074ce0->objMain;
    SetEntrySlotsVisible(container, FindWidgetById(container, 3), 1);

    value = data_0206085c;
    digit = 0;
    do {
        container = data_ov013_02074ce0->objMain;
        SetEntrySlotsVisible(container, FindWidgetById(container, digit + 10), 1);
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b96c0(container, FindWidgetById(container, digit + 10), (u16)(value % 10));
        digit++;
        value /= 10;
    } while (value != 0);

    MI_CpuFill8(&data_ov013_02074ce0->view, 0, sizeof(AvatarView));
    MI_CpuFill8(&data_ov013_02074ce0->savedCard, 0, sizeof(CardHeader));
    LoadAvatarObjPalette(FALSE);
    DispatchContextCommand(0, func_ov013_02070cb4(), 0, &card);
    ctx = data_ov013_02074ce0;
    ctx->savedCard = card.header;
    ctx->view.card = &ctx->savedCard;
    ResetSelectionView(&data_ov013_02074ce0->view);
    data_ov013_02074ce0->view.alpha = 200;
    data_ov013_02074ce0->view.flags.layer = 1;
    data_ov013_02074ce0->view.pos.x = 0xc6000;
    data_ov013_02074ce0->view.pos.y = 0x64000;
    ctx = data_ov013_02074ce0;
    func_ov002_02067c10(ctx->objMain, &ctx->view);
    ctx = data_ov013_02074ce0;
    SetGroupSlotsVisible(ctx->objMain, &ctx->view, 1);
    OpenPanelTextWindow(0, 1);
    *(vu32 *)0x0400001c = 0x1b50000;
    data_ov013_02074ce0->flags99.visible = 1;
}
