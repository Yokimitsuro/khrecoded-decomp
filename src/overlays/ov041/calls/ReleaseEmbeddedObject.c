#include "nitro/types.h"

extern void ReleaseResourceAndDetach(void *node);

void ReleaseEmbeddedObject(u8 *owner) {
    ReleaseResourceAndDetach(owner + 0x3a8);
}
