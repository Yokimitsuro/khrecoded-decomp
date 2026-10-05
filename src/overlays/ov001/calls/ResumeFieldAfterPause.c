#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x480];
    u32 unk_480_0 : 3;
    u32 restoreBrightness : 1;
    u32 isPaused : 1;
    u32 unk_480_5 : 9;
    u32 altMenu : 1;
} FieldManager;

typedef struct {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

extern void func_ov001_0207136c(void);
extern void ClosePanelAndResume(void *panel);
extern void SelectActiveEntry(int index);
extern void SetBrightnessAndSyncMain(int value);
extern void SetSecondaryBrightness(int value);
extern void func_ov025_020b6214(int value);
extern u32 func_ov001_0207b3f4(void);
extern void func_ov023_020b6e80(void);
extern void SetPanelReadyState(int a, int b);

BOOL ResumeFieldAfterPause(void *panel) {
    if (!data_ov001_020a04c4.manager->isPaused) {
        return TRUE;
    }
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x100;
    func_ov001_0207136c();
    ClosePanelAndResume(panel);
    SelectActiveEntry(0);
    if (data_ov001_020a04c4.manager->restoreBrightness) {
        SetBrightnessAndSyncMain(0);
        SetSecondaryBrightness(0);
    }
    if (data_ov001_020a04c4.manager->altMenu) {
        func_ov025_020b6214(0);
        data_ov001_020a04c4.manager->altMenu = 0;
    } else if (func_ov001_0207b3f4() == 0) {
        func_ov023_020b6e80();
        SetPanelReadyState(0, 1);
    }
    data_ov001_020a04c4.manager->isPaused = 0;
    return TRUE;
}
