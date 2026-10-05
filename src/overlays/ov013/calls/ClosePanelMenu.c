#include "nitro/types.h"

typedef struct PanelObject PanelObject;

typedef struct PanelState {
    u8 pad_00[0x3];
    s8 resultMode;
    u8 pad_04[0x2bc - 0x4];
    s32 resultState;
    u8 pad_2C0[0x6818 - 0x2c0];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern void func_ov002_0206203c(int selector);
extern void func_ov013_0206eef4(void);
extern void RefreshProgressCaption(void);
extern void func_ov002_020664e4(int mode);
extern int GetCachedSoundParam(void);
extern int func_0204d8cc(int arg0, int arg1);
extern PanelObject *FindWidgetById(void *panel, int id);
extern void func_ov027_020b9604(void *panel, PanelObject *object);
extern void func_ov027_020b96c0(void *panel, PanelObject *object, int mode);
extern void SetEntrySlotsVisible(void *panel, PanelObject *object, int visible);

void ClosePanelMenu(void) {
    PanelObject *object;
    u8 *panel;

    data_ov013_02074ce0->resultState = 0;
    data_ov013_02074ce0->resultMode = 0;
    func_ov002_0206203c(-1);
    func_ov013_0206eef4();
    RefreshProgressCaption();
    object = FindWidgetById(data_ov013_02074ce0->panel, 0);
    func_ov027_020b9604(data_ov013_02074ce0->panel, object);
    object = FindWidgetById(data_ov013_02074ce0->panel, 2);
    func_ov027_020b9604(data_ov013_02074ce0->panel, object);
    object = FindWidgetById(data_ov013_02074ce0->panel, 3);
    func_ov027_020b9604(data_ov013_02074ce0->panel, object);
    panel = data_ov013_02074ce0->panel;
    object = FindWidgetById(panel, 5);
    func_ov027_020b9604(panel, object);
    panel = data_ov013_02074ce0->panel;
    object = FindWidgetById(panel, 5);
    func_ov027_020b96c0(panel, object, 0);
    panel = data_ov013_02074ce0->panel;
    object = FindWidgetById(panel, 6);
    SetEntrySlotsVisible(panel, object, 0);
    func_ov002_020664e4(3);
    if (GetCachedSoundParam() != 22) {
        func_0204d8cc(22, 15);
    }
}
