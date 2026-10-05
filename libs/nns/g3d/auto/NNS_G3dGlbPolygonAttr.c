#include "libs/nns/g3d/g3d_glbstate_internal.h"

void NNS_G3dGlbPolygonAttr(
    int light,
    int polygonMode,
    int cullMode,
    int polygonId,
    int alpha,
    int misc)
{
    NNS_G3dGlb.prmPolygonAttr =
        light |
        (polygonMode << 4) |
        (cullMode << 6) |
        misc |
        (polygonId << 24) |
        (alpha << 16);
}
