#include "nitro/types.h"

extern u8 *data_0205fe0c;
extern int data_0205ffc8;

int func_0202947c(int index)
{
    int byteOffset = index * 4;
    int *counter = (int *)(data_0205fe0c + 0x2dc0 + byteOffset);
    int *kind = (int *)((char *)&data_0205ffc8 + index * 0x18);

    if (*kind == 3 && *counter != 0) {
        u32 slot = *(u16 *)(data_0205fe0c + byteOffset + 0x2d84);
        u8 *byteCounter = data_0205fe0c + 0x28d8 + slot;
        int result;

        *byteCounter = *byteCounter - 1;
        result = *counter - 1;
        *counter = result;
        return result;
    }
    return -1;
}
