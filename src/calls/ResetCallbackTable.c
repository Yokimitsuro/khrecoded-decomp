#include "nitro/types.h"

extern int data_0205fdd4[];
extern int data_0205fdc8[];
extern u8 data_0205fdc4[];

int ResetCallbackTable(void)
{
    int i = 0;
    int zero = i;
    do {
        data_0205fdd4[i] = zero;
        data_0205fdc8[i] = zero;
        i = i + 1;
    } while (i < 3);
    data_0205fdc4[0] = (u8)zero;
    return 1;
}
