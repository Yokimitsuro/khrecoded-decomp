#include "nitro/types.h"

BOOL TryGetFieldHandle_020a3720(int self, u32 *outTriple) {
    u32 handle = *(u32 *)(self + 0x54);
    outTriple[0] = 0;
    outTriple[1] = handle;
    outTriple[2] = 0;
    return *(int *)(self + 0x54) != 0;
}
