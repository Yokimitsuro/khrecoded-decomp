#ifndef NITRO_OS_TICK_INTERNAL_H
#define NITRO_OS_TICK_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef u64 OSTick;

typedef struct OSiTickState {
    u16 useTick;
    u16 padding;
    BOOL needResetTimer;
    volatile OSTick tickCounter;
} OSiTickState;

extern OSiTickState OSi_TickState;

void OS_InitTick(void);
BOOL OS_IsTickAvailable(void);
OSTick OS_GetTick(void);
u16 OS_GetTickLo(void);
void OS_SetTick(OSTick count);
void OSi_CountUpTick(void);

#endif