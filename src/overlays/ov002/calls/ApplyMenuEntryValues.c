#include "nitro/types.h"

typedef struct MenuContext {
    u8 pad_00[0x22];
    u8 flags_b0 : 1;
    u8 hideEntry2 : 1;
    u8 flags_b2 : 6;
    u8 pad_23[0x69e8 - 0x23];
    u8 panel[4];
} MenuContext;

extern MenuContext *data_ov002_0206c464;
extern void *FindWidgetById(void *panel, int elementId);
extern void ApplySelectedSubitemValues(void *panel, void *element, int useAlt);

void ApplyMenuEntryValues(int useAlt)
{
    void *panel;

    panel = data_ov002_0206c464->panel;
    ApplySelectedSubitemValues(panel, FindWidgetById(panel, 1), useAlt);
    if (!data_ov002_0206c464->hideEntry2) {
        panel = data_ov002_0206c464->panel;
        ApplySelectedSubitemValues(panel, FindWidgetById(panel, 2), useAlt);
    }
    panel = data_ov002_0206c464->panel;
    ApplySelectedSubitemValues(panel, FindWidgetById(panel, 3), useAlt);
    panel = data_ov002_0206c464->panel;
    ApplySelectedSubitemValues(panel, FindWidgetById(panel, 4), useAlt);
}
