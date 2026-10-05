#include "nitro/types.h"

#define REG_BG1CNT (*(volatile u16 *)0x0400000a)

typedef struct {
    u16 priority : 2;
    u16 charBase : 4;
    u16 mosaic : 1;
    u16 colorMode : 1;
    u16 screenBase : 5;
    u16 bgExtPltt : 1;
    u16 screenSize : 2;
} BgControl;

typedef enum { BG_SCREEN_SIZE_256x256 } BgScreenSize;
typedef enum { BG_COLOR_MODE_16, BG_COLOR_MODE_256 } BgColorMode;
typedef enum { BG_SCREEN_BASE_0000 } BgScreenBase;
typedef enum { BG_CHAR_BASE_00000 } BgCharBase;
typedef enum { BG_EXT_PLTT_01 } BgExtPltt;

typedef struct {
    void *func;
    void *context;
} DialogCallback;

typedef void (*ScreenCallback)(u32 context, u32 screen);

typedef struct {
    u8 pad_00000[8];
    BOOL active;
    u8 pad_0000c[0x7910 - 0xc];
    u8 savedScreen[0x7f9c - 0x7910];
    u8 dialog[0x11be0 - 0x7f9c];
    DialogCallback callbacks[3];
    u16 callbackFlags[4];
    u8 pad_11c00[0x11e38 - 0x11c00];
    u32 savedColorMode;
    u8 pad_11e3c[0x11eb4 - 0x11e3c];
    u32 currentScreen;
    ScreenCallback onScreenChange;
} ItemPicker;

extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov075_020cde6c(ItemPicker *picker, BOOL closing);
extern u32 func_ov039_020bc638(void);
extern void *G2_GetBG1ScrPtr(void);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern void OpenDefaultDialog(void *dialog, int owner, s16 x, u16 y, u16 width, u16 height, void *text);

static inline void SetBg1Control(BgScreenSize screenSize, BgColorMode colorMode, BgScreenBase screenBase, BgCharBase charBase, BgExtPltt bgExtPltt)
{
    REG_BG1CNT = (u16)((REG_BG1CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) |
                       (charBase << 2) | (bgExtPltt << 13));
}

void OpenItemPicker(ItemPicker *picker, void *onConfirm, void *onCancel, void *onSelect)
{
    DialogCallback confirm;
    DialogCallback cancel;
    DialogCallback select;
    BgControl control;

    PlaySoundEffect(1, 1);
    func_ov075_020cde6c(picker, FALSE);
    picker->active = TRUE;
    picker->currentScreen = 0;
    picker->onScreenChange(func_ov039_020bc638(), 0);
    control = *(volatile BgControl *)&REG_BG1CNT;
    picker->savedColorMode = control.colorMode;
    SetBg1Control((BgScreenSize)control.screenSize, BG_COLOR_MODE_256, (BgScreenBase)control.screenBase,
                  (BgCharBase)control.charBase, (BgExtPltt)control.bgExtPltt);
    MIi_CpuCopy16(picker->savedScreen, G2_GetBG1ScrPtr(), 0x680);
    confirm.func = onConfirm;
    confirm.context = picker;
    picker->callbacks[0] = confirm;
    cancel.func = onCancel;
    cancel.context = picker;
    picker->callbacks[1] = cancel;
    select.func = onSelect;
    select.context = picker;
    picker->callbacks[2] = select;
    picker->callbackFlags[0] = 1;
    picker->callbackFlags[1] = 1;
    picker->callbackFlags[2] = 1;
    picker->callbackFlags[3] = 3;
    OpenDefaultDialog(picker->dialog, 2, 0, 8, 0x1c, 8, NULL);
}
