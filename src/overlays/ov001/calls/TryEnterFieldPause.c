#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x42c];
    s32 lockCount;
    u8 pad_430[0x47c - 0x430];
    s32 busy;
    u32 isSliding : 1;
    u32 unk_480_1 : 2;
    u32 resumePending : 1;
    u32 isPaused : 1;
    u32 menuRequested : 1;
    u32 unk_480_6 : 8;
    u32 alternateWidgets : 1;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

extern u32 func_ov001_02064490(void);
extern BOOL func_ov001_020645c8(u32 value);
extern BOOL IsSceneModeThreeOrSix(void);
extern BOOL IsHudFlag7Set(void);
extern BOOL IsFieldFlag10Set(void);
extern BOOL IsHudFlag9Set(void);
extern BOOL IsSessionIdle(void);
extern int func_0202c44c(void);
extern void OpenFieldMenuMode(u32 kind);
extern void SelectActiveEntry(int index);
extern void SuspendFieldForPause(void);
extern BOOL CanOpenFieldMenu(void);
extern u32 func_ov001_0207b3f4(void);
extern void SetAlternateMenuWidgets(int enabled);
extern u32 SetPanelFieldA0(u32 mode);
extern BOOL OpenPanel(int panel);

BOOL TryEnterFieldPause(int panel)
{
    if (data_ov001_020a04c4.manager->isPaused == 1) {
        return TRUE;
    }
    if (data_ov001_020a04c4.manager->lockCount != 0) {
        return FALSE;
    }
    if (func_ov001_02064490()) {
        if (data_ov001_020a04c4.manager->isPaused == 1) {
            return TRUE;
        }
        return FALSE;
    }
    if (func_ov001_020645c8(0x363e)) {
        return FALSE;
    }
    if (!IsSceneModeThreeOrSix()) {
        return FALSE;
    }
    if (!IsHudFlag7Set() && !IsFieldFlag10Set() && !IsHudFlag9Set() && data_ov001_020a04c4.manager->busy == 0) {
        if (IsSessionIdle()) {
            func_0202c44c();
            OpenFieldMenuMode(7);
            data_ov001_020a04c4.manager->menuRequested = 1;
            data_ov001_020a04c4.manager->resumePending = 1;
            return FALSE;
        }
        data_ov001_020a04c4.manager->isPaused = 1;
        SelectActiveEntry(1);
        SuspendFieldForPause();
        if (CanOpenFieldMenu() && func_ov001_0207b3f4() == 2) {
            SetAlternateMenuWidgets(1);
            data_ov001_020a04c4.manager->alternateWidgets = 1;
            SetPanelFieldA0(0);
        }
        OpenPanel(panel);
    } else {
        data_ov001_020a04c4.manager->isPaused = 1;
        SelectActiveEntry(1);
        SuspendFieldForPause();
        OpenPanel(panel);
        data_ov001_020a04c4.manager->resumePending = 0;
    }
    return TRUE;
}
