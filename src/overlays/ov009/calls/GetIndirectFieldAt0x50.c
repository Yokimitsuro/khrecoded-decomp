#include "nitro/types.h"

u32 GetIndirectFieldAt0x50(int obj) {
    return *(u32 *)(*(int *)(obj + 8) + 0x50);
}
