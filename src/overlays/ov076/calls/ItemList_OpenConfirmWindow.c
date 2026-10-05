#include "nitro/types.h"

typedef enum { GX_BG_SCRSIZE_TEXT_256x256 = 0 } GXBGScreenSizeText;
typedef enum { GX_BG_COLORMODE_16 = 0, GX_BG_COLORMODE_256 = 1 } GXBGColorMode;
typedef enum { GX_BG_SCRBASE_0x0000 = 0 } GXBGScrBase;
typedef enum { GX_BG_CHARBASE_0x00000 = 0 } GXBGCharBase;
typedef enum { GX_BG_EXTPLTT_01 = 0 } GXBGExtPltt;

typedef struct {
    u16 priority : 2;
    u16 charBase : 4;
    u16 mosaic : 1;
    u16 colorMode : 1;
    u16 screenBase : 5;
    u16 bgExtPltt : 1;
    u16 screenSize : 2;
} GXBg01Control;

typedef void (*ScreenHook)(void *target, int arg);

typedef struct ChoiceHandler {
    void *callback;
    void *owner;
} ChoiceHandler;

typedef struct ItemScreen {
    u8 pad_00000[0x8];
    s32 windowOpen;
    u8 pad_0000c[0x7910 - 0xc];
    u8 bg1Backup[0x7f9c - 0x7910];
    u8 window[0x11be0 - 0x7f9c];
    ChoiceHandler choices[3];
    u16 choiceEnabled[3];
    u16 choiceCount;
    u8 pad_11c00[0x11e38 - 0x11c00];
    s32 colorMode;
    u8 pad_11e3c[0x11eb4 - 0x11e3c];
    s32 hookActive;
    ScreenHook hook;
} ItemScreen;

#define REG_BG1CNT (*(volatile u16 *)0x0400000a)

static inline GXBg01Control G2_GetBG1Control(void)
{
    return *(volatile GXBg01Control *)0x0400000a;
}

static inline void G2_SetBG1Control(GXBGScreenSizeText screenSize, GXBGColorMode colorMode, GXBGScrBase screenBase,
                                    GXBGCharBase charBase, GXBGExtPltt bgExtPltt)
{
    REG_BG1CNT = (u16)((REG_BG1CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) |
                       (charBase << 2) | (bgExtPltt << 13));
}

static inline ChoiceHandler MakeChoiceHandler(void *callback, void *owner)
{
    ChoiceHandler handler;
    handler.callback = callback;
    handler.owner = owner;
    return handler;
}

extern void PlaySoundEffect(int id, int channel);
extern void func_ov076_020c9c7c(ItemScreen *screen, BOOL closing);
extern void *func_ov039_020bc638(void);
extern void *G2_GetBG1ScrPtr(void);
extern void MIi_CpuCopy16(void *src, void *dst, u32 size);
extern void MenuPanel_InitStandard(void *panel, int owner, int x, int y, u16 width, u16 height, int arg7);

void ItemList_OpenConfirmWindow(ItemScreen *screen, void *onYes, void *onNo, void *onCancel)
{
    GXBg01Control control;

    PlaySoundEffect(1, 1);
    func_ov076_020c9c7c(screen, FALSE);
    screen->windowOpen = 1;
    screen->hookActive = 0;
    screen->hook(func_ov039_020bc638(), 0);
    control = G2_GetBG1Control();
    screen->colorMode = control.colorMode;
    G2_SetBG1Control((GXBGScreenSizeText)control.screenSize, GX_BG_COLORMODE_256, (GXBGScrBase)control.screenBase,
                     (GXBGCharBase)control.charBase, (GXBGExtPltt)control.bgExtPltt);
    MIi_CpuCopy16(screen->bg1Backup, G2_GetBG1ScrPtr(), 0x680);
    screen->choices[0] = MakeChoiceHandler(onYes, screen);
    screen->choices[1] = MakeChoiceHandler(onNo, screen);
    screen->choices[2] = MakeChoiceHandler(onCancel, screen);
    screen->choiceEnabled[0] = 1;
    screen->choiceEnabled[1] = 1;
    screen->choiceEnabled[2] = 1;
    screen->choiceCount = 3;
    MenuPanel_InitStandard(screen->window, 2, 0, 8, 0x1c, 8, 0);
}
