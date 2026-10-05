#include "nitro/types.h"

typedef struct {
    u32 resourceId;
    u8 pad_04[0x90];
    u8 animState[0xd8];
    u8 blendTable[0x2c];
    u32 sceneReady;
    u32 animationFinished;
} Panel;

extern int GetLanguageIndex(void);
extern void InitSharedRecordAndDispatch(void *animState, u32 resourceKey, int flags, int count);
extern void selectJointAnimationBlend(void *animState, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void InitPanelCamera(Panel *panel);

void InitPanelScene(Panel *panel)
{
    if (panel->sceneReady != 0) {
        return;
    }
    InitSharedRecordAndDispatch(panel->animState,
                  ((panel->resourceId + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((GetLanguageIndex() != 0) + 3) & 0x1ff,
                  1, 0xe);
    selectJointAnimationBlend(panel->animState, 0, panel->blendTable, 0);
    selectJointAnimationBlend(panel->animState, 2, panel->blendTable, 0);
    panel->animationFinished = 0;
    InitPanelCamera(panel);
    panel->sceneReady = 1;
}
