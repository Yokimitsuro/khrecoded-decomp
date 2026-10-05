#include "libs/nns/g3d/g3d_glbstate_internal.h"

void NNS_G3dGlbGetViewPort(int *px1, int *py1, int *px2, int *py2)
{
    if (px1) {
        *px1 = NNS_G3dGlb.prmViewPort & 0xff;
    }
    if (py1) {
        *py1 = (NNS_G3dGlb.prmViewPort >> 8) & 0xff;
    }
    if (px2) {
        *px2 = (NNS_G3dGlb.prmViewPort >> 16) & 0xff;
    }
    if (py2) {
        *py2 = (NNS_G3dGlb.prmViewPort >> 24) & 0xff;
    }
}
