#include "nitro/types.h"

typedef struct MenuContext {
    u8 pad_00[8];
    s32 unk_08;
    u8 pad_0c[0x69e8 - 0xc];
    u8 panel[4];
} MenuContext;

extern MenuContext *data_ov002_0206c464;
extern void *FindWidgetById(void *panel, int elementId);
extern void ApplySelectedSubitemValues(void *panel, void *element, int useAlt);
extern void func_ov027_020b9640(void *panel, void *element);
extern void func_ov002_020666c8(u32 value);

void ResetMenuElement5(void)
{
    void *panel;

    panel = data_ov002_0206c464->panel;
    ApplySelectedSubitemValues(panel, FindWidgetById(panel, 5), 1);
    panel = data_ov002_0206c464->panel;
    func_ov027_020b9640(panel, FindWidgetById(panel, 5));
    func_ov002_020666c8(0);
    data_ov002_0206c464->unk_08 = 0;
}
