#include "nitro/types.h"

typedef struct PanelEntry {
    u8 pad_00[0x14];
    int animSlot;
} PanelEntry;

typedef struct PanelWork {
    u8 pad_0000[0x14];
    int mode;
    u8 pad_0018[0x148];
    u8 panel[0x647c];
    void *animOwner;
} PanelWork;

extern PanelWork *data_ov015_020812e0;

extern PanelEntry *FindWidgetById(void *panel, int slot);
extern void SetWidgetRootDpadEnabled(void *panel, int value);
extern void SetWidgetRootTouchEnabled(void *panel, int value);
extern void SetSlotAnimSequence(void *owner, int slot, int sequence);
extern void func_ov015_020779a4(int a, int b);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void OnPanelSlot1Selected(void)
{
    PanelEntry *entry = FindWidgetById(data_ov015_020812e0->panel, 1);

    if (entry != NULL) {
        SetSlotAnimSequence(data_ov015_020812e0->animOwner, entry->animSlot, 1);
    }
    SetWidgetRootDpadEnabled(data_ov015_020812e0->panel, 0);
    SetWidgetRootTouchEnabled(data_ov015_020812e0->panel, 0);
    data_ov015_020812e0->mode = 6;
    func_ov015_020779a4(0x24, 0x1f);
    PlaySoundEffect(2, 1);
}
