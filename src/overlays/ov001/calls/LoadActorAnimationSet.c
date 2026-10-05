#include "nitro/types.h"

extern BOOL InitSharedRecordThenTexture(void *animSet, void *model, int archiveId, int resourceKind);

void LoadActorAnimationSet(void *animSet, void *model, int archiveId)
{
    InitSharedRecordThenTexture(animSet, model, archiveId, 11);
}
