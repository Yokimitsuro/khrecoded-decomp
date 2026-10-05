#include "nitro/types.h"

typedef enum { GX_BG_SCRSIZE_TEXT_256x256 = 0 } GXBGScreenSizeText;
typedef enum { GX_BG_COLORMODE_16 = 0 } GXBGColorMode;
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

typedef struct {
    int redrawing;
    int unk_04;
    u8 pad_08[0x11e30];
    int colorMode;
    int drawArg;
} Bg1Screen;

extern void *G2_GetBG1CharPtr(void);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern void func_ov075_020d0034(Bg1Screen *screen, int drawArg);

#define REG_BG1CNT (*(volatile u16 *)0x0400000a)

static inline GXBg01Control G2_GetBG1Control(void) {
    return *(volatile GXBg01Control *)0x0400000a;
}

static inline void G2_SetBG1Control(GXBGScreenSizeText screenSize, GXBGColorMode colorMode, GXBGScrBase screenBase, GXBGCharBase charBase, GXBGExtPltt bgExtPltt) {
    REG_BG1CNT = (u16)((REG_BG1CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) | (bgExtPltt << 13));
}

BOOL ClearBg1AndRedraw(Bg1Screen *screen) {
    GXBg01Control control;
    MIi_CpuClearFast(0, G2_GetBG1CharPtr(), 0x5040);
    control = G2_GetBG1Control();
    G2_SetBG1Control((GXBGScreenSizeText)control.screenSize, (GXBGColorMode)screen->colorMode, (GXBGScrBase)control.screenBase, (GXBGCharBase)control.charBase, (GXBGExtPltt)control.bgExtPltt);
    screen->unk_04 = 0;
    screen->redrawing = 1;
    func_ov075_020d0034(screen, screen->drawArg);
    screen->redrawing = 0;
    return TRUE;
}
