#include "nitro/types.h"

typedef struct PanelElement PanelElement;

typedef struct PanelState {
    u8 pad_0000[0x6ac0];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov015_0207e960;
extern PanelElement *FindWidgetById(void *panel, int elementId);
extern void func_ov027_020b9640(void *panel, PanelElement *element);
extern u32 DispatchContextCommand(u32 command, u32 value, u32 extra, void *buffer);
extern void func_ov002_02066a68(void);

void ResetPanelMenuElements(void)
{
    u8 *panel;

    panel = data_ov015_0207e960->panel;
    func_ov027_020b9640(panel, FindWidgetById(panel, 11));
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9640(panel, FindWidgetById(panel, 30));
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9640(panel, FindWidgetById(panel, 31));
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9640(panel, FindWidgetById(panel, 32));
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9640(panel, FindWidgetById(panel, 33));
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9640(panel, FindWidgetById(panel, 9));
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9640(panel, FindWidgetById(panel, 17));
    DispatchContextCommand(0x80000015, 1, 0, NULL);
    func_ov002_02066a68();
}
