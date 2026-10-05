#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Ov037ContextView {
    u8 pad_000[0x70];
    u8 model[0xa4];
    VecFx32 cameraOffset;
    u8 pad_120[0x54];
    u8 animation[0x80];
} Ov037ContextView;

extern Ov037ContextView *gContinueScreenContext;
extern const VecFx32 data_ov037_020bb650;
extern char sOv037_BaChSoTex0Z_020bb724[];
extern char sOv037_BaChSoMdl0PZ_020bb734[];
extern char sOv037_CntSoanmPZ_020bb748[];
extern void *func_0202c4a0(char *path, u32 flags);
extern void InitSharedRecordAndDispatchAlt(void *dst, char *name, void *info, int flags);
extern BOOL InitSharedRecordThenTexture(void *dst, void *src, char *name, int flags);
extern void selectJointAnimationBlend(void *model, u16 trackIndex, void *animation, int blend);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void LoadMenuModelResources(void)
{
    VecFx32 offset = data_ov037_020bb650;
    void *archive;
    int track;

    archive = func_0202c4a0(sOv037_BaChSoTex0Z_020bb724, 0xe);
    InitSharedRecordAndDispatchAlt(gContinueScreenContext->model, sOv037_BaChSoMdl0PZ_020bb734, archive, 0xe);
    InitSharedRecordThenTexture(gContinueScreenContext->animation, gContinueScreenContext->model, sOv037_CntSoanmPZ_020bb748, 0xe);
    for (track = 0; track < 5; track++) {
        selectJointAnimationBlend(gContinueScreenContext->model, track, gContinueScreenContext->animation, 0);
    }
    gContinueScreenContext->cameraOffset = offset;
    NNSi_FndFreeFromDefaultHeap(archive);
}
