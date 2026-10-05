#include "nitro/types.h"

extern u32 data_ov002_0206c464;
extern u32 FindWidgetById(u32 panel, u32 index);
extern void SetFocusedWidget(u32 panel, u32 element);
extern void DrawMenuLabels(void);
extern void func_ov002_02064f6c(u32 state);
extern void PlaySoundEffect(u32 seqArcNo, u32 index);

void SelectMenuEntry3(void) {
    u32 element;

    *(u8 *)(data_ov002_0206c464 + 3) = 2;
    element = FindWidgetById(data_ov002_0206c464 + 0x69e8, 3);
    SetFocusedWidget(data_ov002_0206c464 + 0x69e8, element);
    DrawMenuLabels();
    func_ov002_02064f6c(2);
    PlaySoundEffect(2, 1);
}
