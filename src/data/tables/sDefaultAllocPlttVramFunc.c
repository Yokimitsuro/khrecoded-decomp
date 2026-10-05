#include "nitro/types.h"

extern void Gfd_DefaultAllocPlttVram(void); /* func */

void (*sDefaultAllocPlttVramFunc[1])(void) = {
    Gfd_DefaultAllocPlttVram, /* func */
};
