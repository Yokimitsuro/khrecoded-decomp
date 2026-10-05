#include "nitro/types.h"

u16 GetLinkedAngleOffset(int entity)
{
    return *(u16 *)(*(int *)(entity + 0x230) + 0x80) - 0x8000;
}
