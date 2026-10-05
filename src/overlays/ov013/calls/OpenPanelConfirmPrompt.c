#include "nitro/types.h"

typedef struct PanelObject PanelObject;

typedef struct PanelState {
    u8 pad_00[0x9a];
    u8 mode : 2;
    u8 unk_9A_2 : 1;
    u8 isLocked : 1;
    u8 pad_9B[0x2bc - 0x9b];
    s32 resultState;
    u8 pad_2C0[0x6818 - 0x2c0];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern void RefreshProgressCaption(void);
extern void func_ov013_02070a50(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern int func_ov002_020621c4(int textIndex, int unused);
extern void func_ov002_02061d58(int window, int x, int y, int palette, int width, int height, int text, int flags);
extern PanelObject *FindWidgetById(void *panel, int id);
extern void func_ov027_020b9604(void *panel, PanelObject *object);
extern void func_ov027_020b96c0(void *panel, PanelObject *object, int mode);
extern void func_ov027_020b97d8(void *panel, PanelObject *object, int mode);
extern void SetEntrySlotsVisible(void *panel, PanelObject *object, int visible);

void OpenPanelConfirmPrompt(void) {
    PanelObject *object;
    u8 *panel;

    data_ov013_02074ce0->resultState = 0;
    data_ov013_02074ce0->isLocked = TRUE;
    RefreshProgressCaption();
    PlaySoundEffect(2, 3);
    func_ov013_02070a50();
    *(vu16 *)0x04001008 = (u16)((*(vu16 *)0x04001008 & ~3) | 2);
    *(vu16 *)0x0400100a = (u16)((*(vu16 *)0x0400100a & ~3) | 3);
    *(vu16 *)0x0400100c = (u16)((*(vu16 *)0x0400100c & ~3) | 1);
    *(vu16 *)0x0400100e = (u16)(*(vu16 *)0x0400100e & ~3);
    func_ov002_02061d58(1, 0x80, 0x41, 2, 6, 10, func_ov002_020621c4(0x6f, 0), 0);
    panel = data_ov013_02074ce0->panel;
    object = FindWidgetById(panel, 4);
    SetEntrySlotsVisible(panel, object, 1);
    panel = data_ov013_02074ce0->panel;
    object = FindWidgetById(panel, 0);
    func_ov027_020b9604(panel, object);
    panel = data_ov013_02074ce0->panel;
    object = FindWidgetById(panel, 4);
    func_ov027_020b97d8(panel, object, 0);
    panel = data_ov013_02074ce0->panel;
    object = FindWidgetById(panel, 5);
    func_ov027_020b9604(panel, object);
    panel = data_ov013_02074ce0->panel;
    object = FindWidgetById(panel, 5);
    func_ov027_020b96c0(panel, object, 0);
}
