#include "nitro/types.h"

void ResetFieldsToDefault(u32 entity) {
    *(u32 *)(entity + 0x98) = 0xffffff00;
    *(u32 *)(entity + 0x9c) = 1;
}
