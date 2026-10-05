#include "nitro/types.h"

typedef s32 (*ModeUpdateFunc)(void);

extern s32 *data_ov001_020a04f4;
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void InitFieldSpriteSlots(s32 *context, s32 flag);
extern void func_ov001_0207e26c(s32 *context, s32 flag);
extern void RandomizeFacing(s32 *context, s32 flag);
extern s32 UpdateFallingPieces(void);
extern s32 UpdateSpinningMode(void);

ModeUpdateFunc InitContextForMode(s32 mode)
{
    ModeUpdateFunc update = NULL;
    s32 *context;

    context = NNSi_FndGetCurrentRootHeap();
    data_ov001_020a04f4 = context;
    *context = mode;
    switch (mode) {
    case 0:
        break;
    case 1:
        InitFieldSpriteSlots(context, 1);
        update = UpdateFallingPieces;
        break;
    case 2:
        func_ov001_0207e26c(context, 1);
        update = UpdateSpinningMode;
        break;
    case 3:
        RandomizeFacing(context, 1);
        update = UpdateSpinningMode;
        break;
    }
    return update;
}
