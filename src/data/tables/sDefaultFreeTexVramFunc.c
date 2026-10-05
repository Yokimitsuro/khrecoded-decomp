#include "nitro/types.h"

extern void Gfd_DefaultFreeTexVram(void); /* func */

void (*sDefaultFreeTexVramFunc[1])(void) = {
    Gfd_DefaultFreeTexVram, /* func */
};
