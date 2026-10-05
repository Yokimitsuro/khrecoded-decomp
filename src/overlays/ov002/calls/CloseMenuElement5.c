#include "nitro/types.h"

typedef struct MenuContext {
    u8 pad_00[0x69e8];
    u8 panel[4];
} MenuContext;

extern MenuContext *data_ov002_0206c464;
extern void *FindWidgetById(void *panel, int elementId);
extern void ApplySelectedSubitemValues(void *panel, void *element, int useAlt);
extern void func_ov027_020b9604(void *panel, void *element);
extern void func_ov027_020b96c0(void *panel, void *element, int value);
extern void func_ov002_02066a68(void);

void CloseMenuElement5(void)
{
    void *panel;

    panel = data_ov002_0206c464->panel;
    ApplySelectedSubitemValues(panel, FindWidgetById(panel, 5), 0);
    panel = data_ov002_0206c464->panel;
    func_ov027_020b9604(panel, FindWidgetById(panel, 5));
    panel = data_ov002_0206c464->panel;
    func_ov027_020b96c0(panel, FindWidgetById(panel, 5), 0);
    func_ov002_02066a68();
}
