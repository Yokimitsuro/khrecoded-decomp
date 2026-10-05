#include "nitro/types.h"

#define TAG_BCA0 0x30414342
#define TAG_BMA0 0x30414d42
#define TAG_BTA0 0x30415442
#define TAG_BVA0 0x30415642
#define TAG_BMD0 0x30444d42
#define TAG_BTP0 0x30505442
#define TAG_BTX0 0x30585442

extern s32 SetupResourceTextures(u32 tag, void *resource, void *heap, u32 baseTag);

s32 ValidateResourceTagAndDispatch(void *resource, void *heap, void *unused, void *arg)
{
    u32 tag = *(u32 *)resource;

    if (tag > TAG_BVA0) {
        goto Upper;
    }
    if (tag >= TAG_BVA0) {
        goto ReturnOne;
    }
    if (tag > TAG_BMA0) {
        goto LowerHigh;
    }
    if (tag >= TAG_BMA0) {
        goto ReturnOne;
    }
    if (tag == TAG_BCA0) {
        goto ReturnOne;
    }
    goto ReturnZero;

LowerHigh:
    if (tag == TAG_BTA0) {
        goto ReturnOne;
    }
    goto ReturnZero;

Upper:
    if (tag > TAG_BTP0) {
        goto BTX0Check;
    }
    if (tag >= TAG_BTP0) {
        goto ReturnOne;
    }
    if (tag == TAG_BMD0) {
        goto BMD0Call;
    }
    goto ReturnZero;

BTX0Check:
    if (tag != TAG_BTX0) {
        goto ReturnZero;
    }
    return SetupResourceTextures(tag, resource, 0, TAG_BVA0);

BMD0Call:
    return SetupResourceTextures(tag, resource, heap, TAG_BVA0);

ReturnOne:
    return 1;
ReturnZero:
    return 0;
}
