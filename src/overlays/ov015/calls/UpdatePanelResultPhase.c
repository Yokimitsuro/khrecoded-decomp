#include "nitro/types.h"

typedef struct {
    u8 pad_0000[4];
    s8 pendingCount;
    u8 pad_0005[0xdb];
    u8 flags0;
    u8 flags1Low : 4;
    u8 resultShown : 1;
    u8 flags1Mid : 2;
    u8 confirmShown : 1;
    u8 pad_00E2[2];
    int phase;
    u8 pad_00E8[4];
    int selectedEntry;
    u8 pad_00F0[0x69d0];
    u8 widgets[4];
} PanelContext;

extern PanelContext *data_ov015_0207e960;

extern void *FindWidgetById(void *widgets, int id);
extern void UpdateWidgetRootOnly(void *widgets, int id);
extern BOOL IsWidgetMoveFinished(void *widget);
extern void SetEntrySlotsVisible(void *widgets, void *widget, BOOL visible);
extern BOOL AreAllWidgetMovesFinished(void *widgets);
extern void func_ov002_020664f4(int frames);
extern BOOL func_ov002_0206655c(void);
extern void func_ov015_0206c6bc(void);
extern void func_ov015_02070af8(int mode);

void UpdatePanelResultPhase(void) {
    void *widget;

    switch (data_ov015_0207e960->phase) {
    case 0:
        widget = FindWidgetById(data_ov015_0207e960->widgets, data_ov015_0207e960->selectedEntry + 1);
        UpdateWidgetRootOnly(data_ov015_0207e960->widgets, 0);
        if (IsWidgetMoveFinished(widget)) {
            SetEntrySlotsVisible(data_ov015_0207e960->widgets, widget, FALSE);
        }
        if (AreAllWidgetMovesFinished(data_ov015_0207e960->widgets)) {
            func_ov002_020664f4(3);
            data_ov015_0207e960->phase = 20;
        }
        break;
    case 20:
        if (func_ov002_0206655c()) {
            data_ov015_0207e960->phase = 40;
        }
        break;
    case 40:
        data_ov015_0207e960->flags0 |= 8;
        data_ov015_0207e960->resultShown = FALSE;
        data_ov015_0207e960->confirmShown = FALSE;
        func_ov015_0206c6bc();
        func_ov015_02070af8(5);
        data_ov015_0207e960->pendingCount--;
        break;
    }
}
