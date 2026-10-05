#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xcf50];
    int optionToggle;
} SceneWork;

extern int func_ov093_020c2368(SceneWork *work);
extern void SetSlotAnimFlag(int side, int slotIndex, int value, SceneWork *work);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void ToggleSceneOption(SceneWork *work)
{
    BOOL visible;

    if (func_ov093_020c2368(work) != 6) {
        return;
    }
    work->optionToggle = (work->optionToggle + 1) % 2;
    visible = TRUE;
    if (work->optionToggle == 1) {
        visible = FALSE;
    }
    SetSlotAnimFlag(0, 2, visible, work);
    PlaySoundEffect(0, 1);
}
