#include "nitro/types.h"

typedef struct {
    s32 selectedEntry;
    s32 listMode;
} MenuScene;

extern void SetPanelSlotFlag(int listIndex, int slotIndex, BOOL enabled, MenuScene *scene);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void ToggleListMode(MenuScene *scene)
{
    scene->listMode = (scene->listMode + 1) % 2;
    SetPanelSlotFlag(0, 0, scene->listMode != 1, scene);
    PlaySoundEffect(0, 1);
}
