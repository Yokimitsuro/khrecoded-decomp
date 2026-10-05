#include "nitro/types.h"

typedef struct PanelPoint {
    s32 x;
    s32 y;
} PanelPoint;

typedef struct PanelWidget PanelWidget;

typedef struct PanelLayoutState {
    u8 pad_000[0x9c];
    PanelPoint framePoints[9];
    PanelPoint iconPoints[9];
    PanelPoint digitPoints[9];
    PanelPoint badgePoints[9];
    PanelPoint markPoints[9];
    u8 pad_204[0x6818 - 0x204];
    u8 panel[0xd150 - 0x6818];
    PanelWidget *frameWidgets[9];
    PanelWidget *iconWidgets[9];
    PanelWidget *digitWidgets[27];
} PanelLayoutState;

extern PanelLayoutState *data_ov013_02074ce0;
extern PanelWidget *FindWidgetById(void *panel, int id);
extern void func_ov027_020b9380(void *panel, PanelWidget *widget, PanelPoint *position, int flag);
extern void func_ov027_020b91e8(void *panel, PanelWidget *widget, PanelPoint *position, int flag);
extern void RefreshPanelSlotDigits(void);

void LayoutPanelSlotWidgets(void)
{
    PanelPoint position;
    PanelLayoutState *state;
    u8 *panel;
    int i;

    for (i = 0; i < 9; i++) {
        func_ov027_020b91e8(data_ov013_02074ce0->panel, data_ov013_02074ce0->frameWidgets[i],
                            &data_ov013_02074ce0->framePoints[i], 0);
        func_ov027_020b91e8(data_ov013_02074ce0->panel, data_ov013_02074ce0->iconWidgets[i],
                            &data_ov013_02074ce0->iconPoints[i], 0);
        state = data_ov013_02074ce0;
        panel = state->panel;
        func_ov027_020b91e8(panel, FindWidgetById(panel, i + 200), &state->badgePoints[i], 0);
        state = data_ov013_02074ce0;
        panel = state->panel;
        func_ov027_020b91e8(panel, FindWidgetById(panel, i + 100), &state->markPoints[i], 0);
        func_ov027_020b9380(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitWidgets[i * 3], &position, 0);
        position.y = data_ov013_02074ce0->digitPoints[i].y;
        func_ov027_020b91e8(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitWidgets[i * 3], &position, 0);
        func_ov027_020b9380(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitWidgets[i * 3 + 1], &position, 0);
        position.y = data_ov013_02074ce0->digitPoints[i].y;
        func_ov027_020b91e8(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitWidgets[i * 3 + 1], &position, 0);
        func_ov027_020b9380(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitWidgets[i * 3 + 2], &position, 0);
        position.y = data_ov013_02074ce0->digitPoints[i].y;
        func_ov027_020b91e8(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitWidgets[i * 3 + 2], &position, 0);
    }
    RefreshPanelSlotDigits();
}
