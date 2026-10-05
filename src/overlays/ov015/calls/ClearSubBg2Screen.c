#include "nitro/types.h"

extern void *G2S_GetBG2ScrPtr(void);
extern void MI_CpuClear32_0x800(void *dst);

void ClearSubBg2Screen(void) {
    MI_CpuClear32_0x800(G2S_GetBG2ScrPtr());
    *(volatile u16 *)0x0400100c &= 0x43;
}
