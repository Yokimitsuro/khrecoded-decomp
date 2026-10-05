#include "nitro/types.h"
#include "nitro/fx_types.h"

#define REG_DISPCNT (*(volatile u32 *)0x04000000)
#define REG_BG1CNT (*(volatile u16 *)0x0400000a)

typedef enum { BG_SCREEN_SIZE_256x256 } BgScreenSize;
typedef enum { BG_COLOR_MODE_16, BG_COLOR_MODE_256 } BgColorMode;
typedef enum { BG_SCREEN_BASE_0000 } BgScreenBase;
typedef enum { BG_CHAR_BASE_00000, BG_CHAR_BASE_14000 = 5 } BgCharBase;
typedef enum { BG_EXT_PLTT_01 } BgExtPltt;

typedef struct {
    u8 pad_00[8];
    u16 flags;
} TouchState;

typedef struct {
    u8 pad_00000[7];
    u8 listDirty;
    u8 redraw;
    u8 pad_00009[0x34 - 9];
    fx32 scrollX;
    fx32 scrollY;
    u8 pad_0003c[0x50 - 0x3c];
    s32 velocityX;
    s32 velocityY;
    u8 pad_00058[0x60 - 0x58];
    BOOL scrollChanged;
    u8 pad_00064[0x70 - 0x64];
    BOOL overview;
    BOOL scrolling;
    BOOL ready;
    u8 pad_0007c[0x88 - 0x7c];
    BOOL animating;
    u8 pad_0008c[0x4ee0 - 0x8c];
    u8 pageTable[0x11fac - 0x4ee0];
    void *currentPage;
    u8 pad_11fb0[0x12dc8 - 0x11fb0];
    BOOL menuOpen;
    u8 pad_12dcc[0x131a4 - 0x12dcc];
    int slotLayout;
    u8 pad_131a8[0x13e64 - 0x131a8];
    u16 noticeTimer;
    u8 pad_13e66[0x13ea0 - 0x13e66];
    BOOL noticeActive;
    u8 pad_13ea4[0x13ecc - 0x13ea4];
    int *slotList;
    u8 pad_13ed0[0x174ec - 0x13ed0];
    fx32 savedScrollX;
    fx32 savedScrollY;
    u8 pad_174f4[0x17524 - 0x174f4];
    BOOL transitioning;
} MatrixMenu;

extern TouchState *func_ov039_020bca20(void);
extern s32 GetDialogInputMode(MatrixMenu *menu);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void *UpdateScreenWidgetLayer(int widget);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void SetScreenLayerDirty(int layerId);
extern void SetEntrySlotsVisible(int a, int *b, int c);
extern void *func_ov027_020ba2c8(void *table, int idx);
extern BOOL IsMatrixInputReady(MatrixMenu *menu);
extern void func_ov075_020c4390(MatrixMenu *menu);

static inline void SetBg1Control(BgScreenSize screenSize, BgColorMode colorMode, BgScreenBase screenBase,
                                 BgCharBase charBase, BgExtPltt bgExtPltt)
{
    REG_BG1CNT = (u16)((REG_BG1CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) |
                       (charBase << 2) | (bgExtPltt << 13));
}

void ToggleMatrixOverview(MatrixMenu *menu)
{
    void *buffer;
    u32 planes;

    if (menu->ready == 0 || menu->menuOpen != 0 || menu->scrolling != 0 || menu->transitioning != 0 ||
        menu->animating != 0 || menu->noticeActive != 0 || menu->noticeTimer != 0 ||
        !IsMatrixInputReady(menu)) {
        return;
    }
    if ((func_ov039_020bca20()->flags & 3) != 0 || GetDialogInputMode(menu) != 0) {
        return;
    }
    if (menu->overview) {
        PlaySoundEffect(1, 3);
        buffer = UpdateScreenWidgetLayer(9);
        menu->overview = FALSE;
        menu->redraw = TRUE;
        if (menu->scrollX != menu->savedScrollX || menu->scrollY != menu->savedScrollY) {
            menu->scrollChanged = TRUE;
            menu->velocityY = 0;
            menu->velocityX = 0;
        }
        SetBg1Control(BG_SCREEN_SIZE_256x256, BG_COLOR_MODE_256, BG_SCREEN_BASE_0000, BG_CHAR_BASE_14000,
                      BG_EXT_PLTT_01);
        planes = (REG_DISPCNT & 0x1f00) >> 8;
        REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | ((planes & ~2) << 8);
        MIi_CpuClearFast(0, buffer, 0x600);
        SetScreenLayerDirty(9);
        SetEntrySlotsVisible(menu->slotLayout, menu->slotList, 0);
        menu->currentPage = func_ov027_020ba2c8(menu->pageTable, 0x58);
        menu->listDirty = TRUE;
        return;
    }
    func_ov075_020c4390(menu);
}
