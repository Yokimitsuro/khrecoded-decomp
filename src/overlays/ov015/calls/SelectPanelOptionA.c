#include "nitro/types.h"

typedef struct PanelContext {
    u8 pad_0000[0xbb];
    u8 selectedOption;
    u8 pad_00bc[0x6ac0 - 0xbc];
    u8 entryManager[1];
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern int FindWidgetById(void *manager, int id);
extern void SetFocusedWidget(void *manager, int entry);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void SelectPanelOptionA(void)
{
    data_ov015_0207e960->selectedOption = 1;
    SetFocusedWidget(data_ov015_0207e960->entryManager, FindWidgetById(data_ov015_0207e960->entryManager, 7));
    PlaySoundEffect(2, 1);
}
