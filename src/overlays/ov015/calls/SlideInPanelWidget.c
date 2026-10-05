#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    int ids[3];
} WidgetIdTable;

typedef struct {
    fx32 x;
    fx32 y;
} WidgetPos;

typedef struct {
    u8 pad_0000[0x34];
    WidgetPos pos;
} Widget;

typedef struct {
    u8 pad_0000[0x6ac0];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov015_0207e960;
extern const WidgetIdTable data_ov015_02079f70;
extern Widget *FindWidgetById(void *panel, int elementId);
extern void ApplySelectedSubitemValues(void *panel, Widget *widget, int useAlt);
extern void func_ov027_020b91e8(void *panel, Widget *widget, const WidgetPos *position, int mode);
extern void StartWidgetMoveTween(void *root, Widget *widget, int duration, const WidgetPos *from, const WidgetPos *to, int mode);
extern void SetEntrySlotsVisible(void *panel, Widget *widget, int visible);
extern void func_ov027_020b9604(void *panel, Widget *widget);

void SlideInPanelWidget(int index)
{
    WidgetIdTable table;
    WidgetPos from;
    WidgetPos to;
    Widget *widget;

    table = data_ov015_02079f70;
    widget = FindWidgetById(data_ov015_0207e960->panel, table.ids[index]);
    ApplySelectedSubitemValues(data_ov015_0207e960->panel, widget, 1);
    from = widget->pos;
    to = widget->pos;
    from.y = 0x12c000;
    func_ov027_020b91e8(data_ov015_0207e960->panel, widget, &from, 0);
    StartWidgetMoveTween(data_ov015_0207e960->panel, widget, 2, &from, &to, 0x9c4);
    SetEntrySlotsVisible(data_ov015_0207e960->panel, widget, 1);
    func_ov027_020b9604(data_ov015_0207e960->panel, widget);
}
