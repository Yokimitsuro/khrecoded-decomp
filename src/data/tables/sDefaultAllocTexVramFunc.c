#include "nitro/types.h"

extern void Gfd_DefaultAllocTexVram(void); /* func */

void (*sDefaultAllocTexVramFunc[1])(void) = {
    Gfd_DefaultAllocTexVram, /* func */
};
