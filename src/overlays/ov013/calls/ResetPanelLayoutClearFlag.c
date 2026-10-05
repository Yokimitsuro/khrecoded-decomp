#include "nitro/types.h"

typedef struct PanelObject PanelObject;

typedef struct PanelState {
    u8 pad_00[0x9a];
    u8 mode : 2;
    u8 unk_9A_2 : 1;
    u8 isLocked : 1;
    u8 pad_9B[0x6818 - 0x9b];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern void func_ov002_020620fc(int selector);
extern void func_ov013_02070aa0(void);
extern void RefreshProgressCaption(void);
extern void func_ov013_0206fbbc(void);
extern void func_ov013_02070e40(s32 useAlt);
extern void func_ov027_020b90b8(void *panel, void *callback);
extern PanelObject *FindWidgetById(void *panel, int id);
extern void func_ov027_020b9640(void *panel, PanelObject *object);
extern void ApplySelectedSubitemValues(void *panel, PanelObject *object, s32 useAlt);

void ResetPanelLayoutClearFlag(void) {
    PanelObject *object;
    u8 *panel;

    func_ov002_020620fc(0);
    func_ov013_02070aa0();
    data_ov013_02074ce0->isLocked = FALSE;
    RefreshProgressCaption();
    func_ov027_020b90b8(data_ov013_02074ce0->panel, NULL);
    func_ov013_0206fbbc();
    object = FindWidgetById(data_ov013_02074ce0->panel, 0);
    func_ov027_020b9640(data_ov013_02074ce0->panel, object);
    object = FindWidgetById(data_ov013_02074ce0->panel, 2);
    func_ov027_020b9640(data_ov013_02074ce0->panel, object);
    object = FindWidgetById(data_ov013_02074ce0->panel, 3);
    func_ov027_020b9640(data_ov013_02074ce0->panel, object);
    panel = data_ov013_02074ce0->panel;
    object = FindWidgetById(panel, 2);
    ApplySelectedSubitemValues(panel, object, 1);
    panel = data_ov013_02074ce0->panel;
    object = FindWidgetById(panel, 3);
    ApplySelectedSubitemValues(panel, object, 1);
    panel = data_ov013_02074ce0->panel;
    object = FindWidgetById(panel, 5);
    func_ov027_020b9640(panel, object);
    func_ov013_02070e40(1);
}
