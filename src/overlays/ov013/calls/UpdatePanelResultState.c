#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x3];
    s8 resultMode;
    u8 pad_04[0x2bc - 0x4];
    s32 resultState;
    u8 pad_2C0[0x2f0 - 0x2c0];
    s8 clearCount;
    u8 pad_2F1[0x6818 - 0x2f1];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern int data_0206085c;
extern BOOL IsButtonBPressed(void);
extern u16 *func_ov002_02062000(void);
extern u32 func_ov002_0206655c(void);
extern void func_ov002_020664f4(int mode);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov013_02070aa0(void);
extern void RefreshProgressCaption(void);
extern void func_ov013_020716e4(int mode);
extern void LeavePanelScene(int mode);
extern void UpdateWidgetRootOnly(void *panel, int value);

void UpdatePanelResultState(void) {
    switch (data_ov013_02074ce0->resultState) {
    case 0:
        if (IsButtonBPressed()) {
            PlaySoundEffect(2, 2);
            func_ov013_02070aa0();
            RefreshProgressCaption();
            func_ov013_020716e4(1);
            return;
        }
        UpdateWidgetRootOnly(data_ov013_02074ce0->panel, *func_ov002_02062000());
        if ((u8)(s8)(data_ov013_02074ce0->resultMode - 1) <= 1) {
            data_ov013_02074ce0->resultState = 5;
        }
        break;
    case 5:
        data_ov013_02074ce0->resultState = 10;
        break;
    case 10:
        if (data_ov013_02074ce0->resultMode == 1) {
            data_0206085c = 0;
            if ((data_ov013_02074ce0->clearCount + 1) % 10 != 0) {
                data_ov013_02074ce0->resultMode = 0;
                func_ov013_02070aa0();
                RefreshProgressCaption();
                data_ov013_02074ce0->resultState = 20;
            } else {
                func_ov002_020664f4(3);
                data_ov013_02074ce0->resultState = 35;
            }
        } else if (data_ov013_02074ce0->resultMode == 2) {
            func_ov013_02070aa0();
            RefreshProgressCaption();
            func_ov013_020716e4(1);
        }
        break;
    case 20:
        func_ov002_020664f4(1);
        data_ov013_02074ce0->resultState = 30;
        break;
    case 30:
        if (func_ov002_0206655c()) {
            func_ov013_020716e4(6);
        }
        break;
    case 35:
        if (func_ov002_0206655c()) {
            LeavePanelScene(0);
        }
        break;
    }
}
