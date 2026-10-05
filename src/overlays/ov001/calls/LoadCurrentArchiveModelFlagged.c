#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ModelArchive {
    u8 pad_000[0x8];
    u32 baseOffsets[0x3f];
    u8 pad_104[0x2];
    u16 currentIndex;
} ModelArchive;

typedef struct LoadedModel {
    u8 pad_00[0xac];
    fx32 unk_AC;
    u8 pad_B0[0x28];
    u8 blendTable[0x2c];
} LoadedModel;

extern void InitSharedRecordAndDispatch(void *dst, int resourceId, void *info, int count);
extern void selectJointAnimationBlend(void *animationState, u16 trackIndex, void *blendTable, s16 blendIndex);

void LoadCurrentArchiveModelFlagged(ModelArchive *archive, u32 fileIndex, LoadedModel *model)
{
    u32 archiveOffset;

    archiveOffset = (archive->baseOffsets[archive->currentIndex] + 0x8000) & 0xfffffc;
    InitSharedRecordAndDispatch(model, (fileIndex & 0x1ff) | (0x80000000 | (archiveOffset << 7)), (void *)1, 0xe);
    model->unk_AC = 1024 * FX32_ONE;
    selectJointAnimationBlend(model, 3, model->blendTable, 0);
}
