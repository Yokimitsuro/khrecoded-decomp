#include "nitro/types.h"

typedef struct ScreenPos {
    u8 pad_00[4];
    s16 x;
    s16 y;
    u8 pad_08[4];
} ScreenPos;

typedef struct MenuPanel {
    u8 pad_00[4];
    s32 state;
} MenuPanel;

typedef struct PadState {
    u8 pad_00[8];
    u16 held;
} PadState;

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x10];
    s32 column;
    u8 pad_00018[0xc];
    MenuPanel panel;
    u8 pad_0002C[0x7fc0 - 0x2c];
    s32 viewMode;
    u8 pad_07FC4[0x11ee0 - 0x7fc4];
    s32 busy;
    u8 pad_11EE4[2];
    s16 slotIndex;
    s16 scrollRow;
    u8 pad_11EEA[2];
    u8 rowHeight;
    u8 pad_11EED[0x11f18 - 0x11eed];
    s32 scrollY;
    u8 pad_11F1C[0x4a074 - 0x11f1c];
    s32 showTutorial;
} SlotMenu;

extern ScreenPos data_ov076_020cd2d4;
extern ScreenPos data_ov076_020cd2e0;
extern ScreenPos data_ov076_020cd2b0;
extern ScreenPos data_ov076_020cd2ec;
extern ScreenPos data_ov076_020cd2f8;

extern PadState *func_ov039_020bca20(void);
extern void *func_ov039_020bc1dc(void);
extern int func_ov076_020c44e0(SlotMenu *menu, int slot);
extern void func_ov076_020c5318(SlotMenu *menu, u16 slot, u16 column, int mode, ScreenPos *pos);
extern BOOL func_ov076_020cbbc0(MenuPanel *panel, SlotMenu *owner, int (*getValue)(SlotMenu *), void (*onClose)(SlotMenu *), ScreenPos *pos, int style);
extern int func_ov076_020c51b0(SlotMenu *menu);
extern int func_ov076_020c51d0(SlotMenu *menu);
extern void func_ov076_020c4f38(SlotMenu *menu);
extern void func_ov076_020c4f54(SlotMenu *menu);
extern void func_ov076_020c83a8(SlotMenu *menu, int messageId);
extern void func_ov076_020ccd50(void *container, BOOL visible);
extern void PlaySoundEffect(int seqArcNo, int index);
extern void func_ov076_020c4464(SlotMenu *menu);
extern void func_ov076_020c53e8(SlotMenu *menu);

void SlotMenu_HandleSlotSelect(SlotMenu *menu)
{
    int slot = menu->slotIndex;
    u8 height;
    int remainder;

    if (menu->panel.state != 0 || menu->viewMode == 3 || menu->busy != 0) {
        return;
    }
    if (func_ov039_020bca20()->held & 3) {
        return;
    }
    if (menu->state == 1) {
    if (menu->column == 2) {
        if (func_ov076_020c44e0(menu, slot)) {
            func_ov076_020c5318(menu, menu->slotIndex, menu->column, 0, &data_ov076_020cd2d4);
            func_ov076_020c5318(menu, menu->slotIndex, menu->column, 0, &data_ov076_020cd2e0);
            if (func_ov076_020cbbc0(&menu->panel, menu, func_ov076_020c51b0, func_ov076_020c4f38, &data_ov076_020cd2d4, 2)) {
                menu->state = 2;
                func_ov076_020ccd50(func_ov039_020bc1dc(), FALSE);
                menu->showTutorial = 1;
                PlaySoundEffect(1, 1);
            } else {
                func_ov076_020c83a8(menu, 0x27);
                menu->state = 3;
                func_ov076_020ccd50(func_ov039_020bc1dc(), FALSE);
            }
        } else {
            PlaySoundEffect(1, 4);
        }
    } else {
        func_ov076_020c5318(menu, menu->slotIndex, menu->column, 0, &data_ov076_020cd2b0);
        func_ov076_020c5318(menu, menu->slotIndex, 0, 0, &data_ov076_020cd2ec);
        func_ov076_020c5318(menu, menu->slotIndex, 0, 0, &data_ov076_020cd2f8);
        if (func_ov076_020cbbc0(&menu->panel, menu, func_ov076_020c51d0, func_ov076_020c4f54, &data_ov076_020cd2b0, 1)) {
            menu->state = 2;
            func_ov076_020ccd50(func_ov039_020bc1dc(), FALSE);
            PlaySoundEffect(1, 1);
        } else {
            *(vu16 *)0x0400000a = (*(vu16 *)0x0400000a & 0x43) | 0x10;
            func_ov076_020c4464(menu);
            func_ov076_020c53e8(menu);
            *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1f00;
        }
    }
    height = menu->rowHeight;
    remainder = menu->scrollY % height;
    if (remainder != 0) {
        if (remainder >= height / 2) {
            menu->scrollRow++;
        }
        menu->scrollY = menu->scrollRow * menu->rowHeight;
    }
    }
}
