#include "nitro/types.h"

typedef struct {
    s32 mode;
    s32 duration;
    s32 startValue;
    s32 endValue;
    u8 pad_10[0xC];
} PanelTween;

typedef struct {
    u8 pad_000[0x47C];
    s32 panelState;
    u32 isSliding : 1;
    u32 unk_480_1 : 31;
    u8 pad_484[0x158];
    PanelTween slideTween;
    u8 pad_5F8[0xC];
    s32 slideOffset;
} FieldManager;

typedef struct {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;
extern BOOL data_0205fde4;

extern void func_02052528(PanelTween *tween, int mode, int startValue, int endValue, int duration);
extern void func_02052570(PanelTween *tween);
extern void SetFieldMenuSuspended(int enable, int arg1);
extern void ClearChoiceHighlight(FieldManager *manager);
extern void BackupSceneVram(FieldManager *manager);

BOOL OpenFieldPanel(void)
{
    FieldManager *manager = data_ov001_020a04c4.manager;

    if (manager->panelState != 0) {
        return FALSE;
    }
    if (data_0205fde4 != FALSE) {
        return FALSE;
    }
    func_02052528(&manager->slideTween, 2, 0, 0x60000, 100);
    func_02052570(&manager->slideTween);
    manager->isSliding = TRUE;
    manager->slideOffset = 0;
    SetFieldMenuSuspended(1, 1);
    manager->panelState = 1;
    ClearChoiceHighlight(manager);
    BackupSceneVram(manager);
    return TRUE;
}
