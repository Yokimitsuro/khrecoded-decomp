#include "nitro/types.h"

typedef struct TickTween {
    u8 data[0x1c];
} TickTween;

typedef struct BgResource {
    u8 pad_00[0x24];
    void *charData;
} BgResource;

typedef struct FieldManager {
    u8 pad_000[0x1c];
    u8 records[0x410];
    void *overlayScreen;
    s32 panelReady;
    u8 pad_434[0x8];
    void *savedBgScreen;
    void *savedBg2Char;
    void *savedBgPalette;
    u8 pad_448[0x34];
    s32 panelState;
    u32 isSliding : 1;
    u32 unk_480_1 : 5;
    u32 use256ColorBg : 1;
    u32 unk_480_7 : 13;
    u32 slotLabelsDirty : 1;
    u32 unk_480_21 : 11;
    u8 pad_484[0xd0];
    TickTween tickerTween;
    u8 pad_570[0x34];
    BgResource *bgResource;
    u8 pad_5a8[0x34];
    TickTween slideTween;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

typedef void (*ScreenLoader)(const void *src, u32 offset, u32 size);

typedef struct WidgetLayerIds {
    int ids[7];
} WidgetLayerIds;

typedef struct ScreenLoaders {
    ScreenLoader loaders[7];
} ScreenLoaders;

extern FieldManagerHandle data_ov001_020a04c4;
extern const WidgetLayerIds data_ov001_0209dd28;
extern const ScreenLoaders gBgScreenLoaders;

extern BOOL func_ov001_02072040(void);
extern void DC_FlushAll(void);
extern void SetupFieldBgLayers(void);
extern void SetFieldMenuSuspended(int enable, int arg1);
extern void func_ov001_0207b4e8(void);
extern void func_ov001_0206e818(void);
extern void *G2_GetBG3ScrPtr(void);
extern void *G2_GetBG1ScrPtr(void);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *memory);
extern u32 func_ov001_0207b3f4(void);
extern void GXS_LoadBG1Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG1Char(const void *src, u32 offset, u32 size);
extern void RegisterEmbeddedObjectIfPending(void);
extern void func_ov001_0207b5f4(void);
extern void *func_ov027_020b9e10(FieldManager *manager, int layer);
extern void func_0202d620(u32 value);
extern void ApplyModeFadeBlend(void);
extern BOOL TryFinishPendingTask(void);
extern void SetPanelReadyState(int readyA, int readyB);
extern void setStopwatchHeld(TickTween *tween, int hold);
extern void RefreshModeWindow(int screen);
extern BOOL IsFieldFlag8Set(void);
extern BOOL IsHudFlag9Set(void);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8230(void *pool, void *record);

void ResumeFieldFromPause(void)
{
    int i;
    int layerCount;
    BOOL overridden;
    FieldManager *manager = data_ov001_020a04c4.manager;
    WidgetLayerIds layers = data_ov001_0209dd28;
    ScreenLoaders screens = gBgScreenLoaders;
    void *charData = manager->bgResource->charData;

    overridden = func_ov001_02072040();
    DC_FlushAll();
    if ((manager->panelState == 0 || manager->panelState == 3) && !overridden) {
        SetupFieldBgLayers();
        SetFieldMenuSuspended(0, 1);
        func_ov001_0207b4e8();
    } else {
        func_ov001_0206e818();
    }
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
    GX_LoadBG3Char(manager->savedBgScreen, 0, 0x5c00);
    GX_LoadBG2Char(manager->savedBg2Char, 0, 0x1000);
    GX_LoadBGPltt(manager->savedBgPalette, 0, 0x200);
    NNSi_FndFreeFromDefaultHeap(manager->savedBgPalette);
    NNSi_FndFreeFromDefaultHeap(manager->savedBg2Char);
    NNSi_FndFreeFromDefaultHeap(manager->savedBgScreen);
    manager->savedBgPalette = NULL;
    manager->savedBg2Char = NULL;
    manager->savedBgScreen = NULL;
    if ((manager->panelState == 0 || manager->panelState == 3) && func_ov001_0207b3f4() == 0) {
        GXS_LoadBG1Char(charData, 0x1000, 0x780);
    }
    GX_LoadBG1Char(charData, 0x5c00, 0x780);
    if (manager->overlayScreen != NULL && manager->use256ColorBg == 1) {
        RegisterEmbeddedObjectIfPending();
        MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
    } else {
        if (func_ov001_0207b3f4() == 2) {
            layerCount = 4;
            func_ov001_0207b5f4();
        } else {
            layerCount = 7;
        }
        for (i = 0; i < layerCount; i++) {
            screens.loaders[i](func_ov027_020b9e10(manager, layers.ids[i]), 0, 0x800);
        }
    }
    func_0202d620(1);
    if (manager->panelState >= 1 && manager->panelState <= 2) {
        ApplyModeFadeBlend();
    }
    if (manager->panelReady != 0 && TryFinishPendingTask()) {
        SetPanelReadyState(1, func_ov001_0207b3f4() == 0);
    }
    setStopwatchHeld(&manager->tickerTween, 0);
    setStopwatchHeld(&manager->slideTween, 0);
    RefreshModeWindow(0);
    if (IsFieldFlag8Set()) {
        if (IsHudFlag9Set()) {
            manager->slotLabelsDirty = 1;
            return;
        }
        func_ov027_020b8230(manager->records, FindActiveRecordById(manager->records, 5));
    }
}
