#include "nitro/types.h"

extern void ReleaseResourceAndDetach(u8 *object);

void ReleaseNestedObjectAt0x30(u8 *obj)
{
    ReleaseResourceAndDetach(obj + 0x30);
}
