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

extern void ResumeFieldFromPause(void);
extern void ClosePanelAndResume(void *panel);
extern void SelectActiveEntry(int index);
extern void SetBrightnessAndSyncMain(int value);
extern void SetSecondaryBrightness(int value);
extern void SetAlternateMenuWidgets(int value);
extern u32 func_ov001_0207b3f4(void);
extern void ApplyScreenAlphaBlend(void);
extern void SetPanelReadyState(int a, int b);

BOOL ResumeFieldAfterPause(void *panel) {
    if (!data_ov001_020a04c4.manager->isPaused) {
        return TRUE;
    }
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x100;
    ResumeFieldFromPause();
    ClosePanelAndResume(panel);
    SelectActiveEntry(0);
    if (data_ov001_020a04c4.manager->restoreBrightness) {
        SetBrightnessAndSyncMain(0);
        SetSecondaryBrightness(0);
    }
    if (data_ov001_020a04c4.manager->altMenu) {
        SetAlternateMenuWidgets(0);
        data_ov001_020a04c4.manager->altMenu = 0;
    } else if (func_ov001_0207b3f4() == 0) {
        ApplyScreenAlphaBlend();
        SetPanelReadyState(0, 1);
    }
    data_ov001_020a04c4.manager->isPaused = 0;
    return TRUE;
}
