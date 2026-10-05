#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x2bc];
    s32 resultState;
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern u32 func_ov002_0206655c(void);
extern BOOL func_ov002_020632ac(void);
extern BOOL IsButtonXPressed(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov002_020664f4(int mode);
extern void func_ov002_020664e4(int mode);
extern void func_ov002_0206203c(int selector);
extern void func_ov013_0206caa4(void);
extern void DrawPlayerCardDetails(void);
extern void func_ov013_020716e4(int mode);
extern void LeavePanelScene(int mode);

void UpdatePanelMenuState(void) {
    switch (data_ov013_02074ce0->resultState) {
    case 0:
        if (func_ov002_0206655c()) {
            data_ov013_02074ce0->resultState = 10;
        }
        break;
    case 10:
        if (func_ov002_020632ac()) {
            PlaySoundEffect(2, 1);
            func_ov002_020664f4(3);
            data_ov013_02074ce0->resultState = 50;
        } else if (IsButtonXPressed()) {
            func_ov002_020664f4(3);
            PlaySoundEffect(2, 3);
            data_ov013_02074ce0->resultState = 60;
        }
        break;
    case 20:
        if (func_ov002_0206655c()) {
            func_ov013_0206caa4();
            func_ov002_0206203c(-1);
            DrawPlayerCardDetails();
            func_ov002_020664e4(1);
            data_ov013_02074ce0->resultState = 30;
        }
        break;
    case 30:
        if (func_ov002_0206655c()) {
            func_ov013_020716e4(1);
        }
        break;
    case 50:
        if (func_ov002_0206655c()) {
            LeavePanelScene(0);
        }
        break;
    case 60:
        if (func_ov002_0206655c()) {
            LeavePanelScene(1);
        }
        break;
    }
}
