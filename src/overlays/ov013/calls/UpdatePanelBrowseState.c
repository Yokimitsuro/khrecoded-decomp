#include "nitro/types.h"

typedef struct ScrollList {
    s32 count;
    s8 index;
    u8 pad_05[3];
    s32 scroll;
} ScrollList;

typedef struct PanelState {
    u8 pad_00[0x3];
    s8 resultMode;
    u8 pad_04[0x98 - 0x4];
    u8 unk_98_0 : 6;
    u8 playsCue : 1;
    u8 pad_99[0x2bc - 0x99];
    s32 resultState;
    u8 pad_2C0[0x2cc - 0x2c0];
    s32 scrollOffset;
    u8 pad_2D0[0x2ec - 0x2d0];
    ScrollList list;
    u8 pad_2F8[0x39c - 0x2f8];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern u32 func_ov002_0206655c(void);
extern BOOL IsButtonXPressed(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov002_020664f4(int mode);
extern u16 *func_ov002_02062000(void);
extern void UpdateWidgetRootOnly(void *panel, int value);
extern u32 ScrollListKeys(u32 keys, ScrollList *list);
extern void func_ov013_020704a0(void);
extern void func_ov013_0206fbbc(void);
extern void RefreshProgressCaption(void);
extern void func_ov013_020716e4(int mode);
extern void LeavePanelScene(int mode);

void UpdatePanelBrowseState(void) {
    switch (data_ov013_02074ce0->resultState) {
    case 0:
        if (func_ov002_0206655c()) {
            if (data_ov013_02074ce0->playsCue) {
                PlaySoundEffect(2, 0xb);
            }
            data_ov013_02074ce0->resultState = 10;
        }
        break;
    case 10:
        if (IsButtonXPressed()) {
            PlaySoundEffect(2, 3);
            func_ov002_020664f4(3);
            data_ov013_02074ce0->resultState = 60;
            break;
        }
        UpdateWidgetRootOnly(data_ov013_02074ce0->panel, *func_ov002_02062000());
        switch (data_ov013_02074ce0->resultMode) {
        case 1:
            func_ov002_020664f4(3);
            data_ov013_02074ce0->resultState = 50;
            break;
        case 2:
            func_ov002_020664f4(3);
            data_ov013_02074ce0->resultState = 40;
            break;
        }
        break;
    case 40:
        if (func_ov002_0206655c()) {
            LeavePanelScene(2);
        }
        break;
    case 50:
        if (func_ov002_0206655c()) {
            ScrollListKeys(0x80, &data_ov013_02074ce0->list);
            data_ov013_02074ce0->scrollOffset = -data_ov013_02074ce0->list.scroll;
            func_ov013_020704a0();
            func_ov013_0206fbbc();
            RefreshProgressCaption();
            if ((data_ov013_02074ce0->list.index + 1) % 10 != 0) {
                func_ov013_020716e4(6);
            } else {
                LeavePanelScene(0);
            }
        }
        break;
    case 60:
        if (func_ov002_0206655c()) {
            LeavePanelScene(1);
        }
        break;
    }
}
