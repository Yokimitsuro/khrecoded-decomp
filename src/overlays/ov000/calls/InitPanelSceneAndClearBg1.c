#include "nitro/types.h"

typedef struct {
    u32 resourceId;
    u8 pad_04[0x90];
    u8 animState[0x78];
    void *model;
    u8 pad_110[0x5c];
    u8 blendTable[0x2c];
    u32 animationActive;
    u32 animationFinished;
} Panel;

extern void InitSharedRecordAndDispatch(void *animState, u32 resourceKey, int flags, int count);
extern void selectJointAnimationBlend(void *animState, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void NNSi_G3dModifyPolygonAttrMask(void *model, BOOL enable, u32 polygonAttrMask);
extern void InitPanelCamera(Panel *panel);
extern void *G2_GetBG1CharPtr(void);
extern void *G2S_GetBG1CharPtr(void);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2S_GetBG1ScrPtr(void);
/* Non-void return keeps the original call scheduling */
extern void *MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern BOOL IsSoundStreamActive(int handleIndex);
extern BOOL PrepareAndStartStream(int handleIndex, u16 streamId);

void InitPanelSceneAndClearBg1(Panel *panel)
{
    InitSharedRecordAndDispatch(panel->animState, ((panel->resourceId + 0x8000) & 0xfffffc) << 7 | 0x80000000, 1, 0xe);
    selectJointAnimationBlend(panel->animState, 0, panel->blendTable, 0);
    selectJointAnimationBlend(panel->animState, 2, panel->blendTable, 0);
    NNSi_G3dModifyPolygonAttrMask(panel->model, TRUE, 0x30);
    NNSi_G3dModifyPolygonAttrMask(panel->model, TRUE, 0x3f000000);
    NNSi_G3dModifyPolygonAttrMask(panel->model, TRUE, 0x1f0000);
    NNSi_G3dModifyPolygonAttrMask(panel->model, TRUE, 0x800);
    panel->animationActive = 1;
    panel->animationFinished = 0;
    InitPanelCamera(panel);
    MIi_CpuClearFast(0, G2_GetBG1CharPtr(), 0xc000);
    MIi_CpuClearFast(0, G2S_GetBG1CharPtr(), 0xc000);
    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG1ScrPtr(), 0x800);
    if (!IsSoundStreamActive(0)) {
        PrepareAndStartStream(0, 0);
    }
}
