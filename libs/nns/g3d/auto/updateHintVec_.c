#include "libs/nns/g3d/g3d_kernel_internal.h"

void updateHintVec_(u32 *hint, const NNSG3dAnmObj *anmObj)
{
    const NNSG3dAnmObj *current = anmObj;

    while (current) {
        int i;
        for (i = 0; i < current->numMapData; ++i) {
            if (current->mapData[i] & NNS_G3D_ANMOBJ_MAPDATA_EXIST) {
                hint[i >> 5] |= 1 << (i & 31);
            }
        }
        current = current->next;
    }
}
