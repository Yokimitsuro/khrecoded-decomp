#include "nitro/types.h"

int NegateFieldValue(u32 entity) {
    return -*(s32 *)(entity + 0x94);
}
