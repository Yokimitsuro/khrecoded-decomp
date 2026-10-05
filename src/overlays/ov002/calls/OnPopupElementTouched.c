#include "nitro/types.h"

typedef struct PanelElement {
    u8 pad_00[0xc];
    int value;
} PanelElement;

typedef struct MenuContext {
    u8 state;
    u8 mode;
    u8 unk_02;
    s8 selectedIndex;
    u8 pad_04[0x1e];
    u8 unk_22_0 : 2;
    u8 hasOption1 : 1;
    u8 hasOption2 : 1;
    u8 unk_22_4 : 4;
    u8 pad_23[0x69e8 - 0x23];
    u8 panel[0x6450];
} MenuContext;

extern MenuContext *data_ov002_0206c464;

extern PanelElement *FindWidgetById(void *panel, int elementId);
extern void func_ov027_020b96c0(void *panel, PanelElement *element, int mode);
extern void DrawMenuLabels(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void OnPopupElementTouched(PanelElement *element)
{
    s8 previous = data_ov002_0206c464->selectedIndex;

    switch (element->value) {
    case 0:
        break;
    case 1:
        if (data_ov002_0206c464->hasOption1) {
            func_ov027_020b96c0(data_ov002_0206c464->panel, FindWidgetById(data_ov002_0206c464->panel, 0x15), 1);
        }
        data_ov002_0206c464->selectedIndex = 0;
        break;
    case 2:
        if (data_ov002_0206c464->hasOption2) {
            func_ov027_020b96c0(data_ov002_0206c464->panel, FindWidgetById(data_ov002_0206c464->panel, 0x16), 1);
        }
        data_ov002_0206c464->selectedIndex = 1;
        break;
    case 3:
        data_ov002_0206c464->selectedIndex = 2;
        break;
    case 4:
        data_ov002_0206c464->selectedIndex = 3;
        break;
    }
    DrawMenuLabels();
    if (previous != data_ov002_0206c464->selectedIndex) {
        PlaySoundEffect(2, 0);
    }
}
