#include "nitro/types.h"

typedef struct PanelWidget {
    u8 pad_00[0xc];
    u32 value;
} PanelWidget;

typedef struct PanelState {
    u8 pad_00[3];
    u8 resultMode;
    u8 pad_04[0xc];
    u32 resultValue;
    u8 pad_14[0x9a - 0x14];
    u8 flags;
    u8 pad_9b[0x2bc - 0x9b];
    s32 scrollPixels;
    u8 pad_2c0[0x6818 - 0x2c0];
    u8 panel[4];
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern void RefreshProgressCaption(void);
extern PanelWidget *FindWidgetById(void *panel, int id);
extern void SetFocusedWidget(void *panel, PanelWidget *widget);
extern void DrawPanelResultCaption(int mode);
extern void func_ov013_02070e40(int mode);
extern void func_ov013_02070a50(void);
extern void SetEntrySlotsVisible(void *panel, PanelWidget *widget, int visible);
extern void func_ov027_020b9604(void *panel, PanelWidget *widget);
extern void ApplySelectedSubitemValues(void *panel, PanelWidget *widget, int flag);
extern void func_ov027_020b90b8(void *panel, void (*callback)(void));
extern void func_ov013_02074420(void);
extern void PlaySoundEffect(int id, int flag);
extern void func_ov027_020b96c0(void *panel, PanelWidget *widget, int flag);

void OpenPanelResultMenu(void)
{
    u8 *panel;

    data_ov013_02074ce0->flags |= 8;
    RefreshProgressCaption();
    SetFocusedWidget(data_ov013_02074ce0->panel, FindWidgetById(data_ov013_02074ce0->panel, 10));
    data_ov013_02074ce0->resultValue = FindWidgetById(data_ov013_02074ce0->panel, 10)->value;
    DrawPanelResultCaption(1);
    data_ov013_02074ce0->resultMode = 0;
    data_ov013_02074ce0->scrollPixels = 0;
    data_ov013_02074ce0->resultMode = 0;
    func_ov013_02070e40(0);
    func_ov013_02070a50();
    SetEntrySlotsVisible(data_ov013_02074ce0->panel, FindWidgetById(data_ov013_02074ce0->panel, 9), 1);
    SetEntrySlotsVisible(data_ov013_02074ce0->panel, FindWidgetById(data_ov013_02074ce0->panel, 10), 1);
    func_ov027_020b9604(data_ov013_02074ce0->panel, FindWidgetById(data_ov013_02074ce0->panel, 0));
    func_ov027_020b9604(data_ov013_02074ce0->panel, FindWidgetById(data_ov013_02074ce0->panel, 2));
    func_ov027_020b9604(data_ov013_02074ce0->panel, FindWidgetById(data_ov013_02074ce0->panel, 3));
    panel = data_ov013_02074ce0->panel;
    ApplySelectedSubitemValues(panel, FindWidgetById(panel, 2), 0);
    panel = data_ov013_02074ce0->panel;
    ApplySelectedSubitemValues(panel, FindWidgetById(panel, 3), 0);
    func_ov027_020b90b8(data_ov013_02074ce0->panel, func_ov013_02074420);
    PlaySoundEffect(2, 1);
    panel = data_ov013_02074ce0->panel;
    func_ov027_020b9604(panel, FindWidgetById(panel, 5));
    panel = data_ov013_02074ce0->panel;
    func_ov027_020b96c0(panel, FindWidgetById(panel, 5), 0);
}
