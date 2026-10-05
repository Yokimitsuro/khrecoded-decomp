#include "nitro/types.h"

void SetFieldAt2C(int obj, u16 value) {
    *(u16 *)(obj + 0x2c) = value;
}
