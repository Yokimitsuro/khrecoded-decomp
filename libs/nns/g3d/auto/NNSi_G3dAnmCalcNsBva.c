#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 frame;
    u8 pad_04[4];
    void *resAnm;
} NNSG3dAnmObj;

typedef struct {
    u8 pad_00[4];
    u16 numFrame;
    u16 numNode;
    u8 pad_08[4];
    u32 visData[1];
} NNSG3dResVisAnm;

void NNSi_G3dAnmCalcNsBva(u32 *result, const NNSG3dAnmObj *anmObj, u32 dataIdx)
{
    const NNSG3dResVisAnm *visAnm = anmObj->resAnm;
    s32 frame = anmObj->frame;
    u32 pos;

    if (frame >= (s32)(visAnm->numFrame << 12)) {
        frame = (visAnm->numFrame << 12) - 1;
    } else if (frame < 0) {
        frame = 0;
    }

    pos = (frame >> 12) * visAnm->numNode + dataIdx;
    *result = visAnm->visData[pos >> 5] & (1 << (pos & 0x1f));
}
