#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PanelElement PanelElement;

typedef struct ElementPos {
    fx32 x;
    fx32 y;
} ElementPos;

typedef struct MenuContext {
    u8 pad_00[0x10];
    fx32 leftSpeed;
    fx32 rightSpeed;
    fx32 leftY;
    fx32 rightY;
    u8 pad_20[0x56c - 0x20];
    u8 panel[0x647c];
} MenuContext;

extern MenuContext *data_ov002_0206c464;

extern PanelElement *FindWidgetById(void *panel, int elementId);
extern void func_ov027_020b9380(void *panel, PanelElement *element, ElementPos *pos, int flag);
extern void func_ov027_020b91e8(void *panel, PanelElement *element, ElementPos *pos, int flag);
extern unsigned int func_0202a9e4(unsigned int range);

void ScrollMenuClouds(void)
{
    ElementPos pos;
    void *panel;

    panel = data_ov002_0206c464->panel;
    func_ov027_020b9380(panel, FindWidgetById(data_ov002_0206c464->panel, 0), &pos, 0);
    pos.x -= data_ov002_0206c464->leftSpeed;
    pos.y = data_ov002_0206c464->leftY;
    if ((pos.x >> 12) < -0x40) {
        pos.x = 0x140000;
        data_ov002_0206c464->leftSpeed = func_0202a9e4(0x1000) + 0x1000;
        data_ov002_0206c464->leftY = (func_0202a9e4(0x30) + 0x10) << 12;
    }
    panel = data_ov002_0206c464->panel;
    func_ov027_020b91e8(panel, FindWidgetById(data_ov002_0206c464->panel, 0), &pos, 0);
    panel = data_ov002_0206c464->panel;
    func_ov027_020b9380(panel, FindWidgetById(data_ov002_0206c464->panel, 1), &pos, 0);
    pos.x += data_ov002_0206c464->rightSpeed;
    pos.y = data_ov002_0206c464->rightY;
    if ((pos.x >> 12) > 0x140) {
        pos.x = -0x40000;
        data_ov002_0206c464->rightSpeed = func_0202a9e4(0x1000) + 0x1000;
        data_ov002_0206c464->rightY = (func_0202a9e4(0x30) + 0x80) << 12;
    }
    panel = data_ov002_0206c464->panel;
    func_ov027_020b91e8(panel, FindWidgetById(data_ov002_0206c464->panel, 1), &pos, 0);
}
