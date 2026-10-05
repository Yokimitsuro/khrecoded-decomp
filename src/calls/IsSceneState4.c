#include "nitro/types.h"

extern u8 *data_0206084c;

BOOL IsSceneState4(void)
{
    return data_0206084c[0xb472e] == 4;
}
