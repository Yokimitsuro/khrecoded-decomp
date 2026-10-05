#include "nitro/types.h"
#include "nnsys/g2d.h"

void ApplyTextColorTag(u16 c, NNSG2dTagCallbackInfo *cbInfo)
{
    switch (c) {
    case 1:
        cbInfo->clr = 0xf2;
        break;
    case 2:
        cbInfo->clr = 0xf6;
        break;
    case 4:
        cbInfo->clr = 0xfa;
        break;
    }
}
