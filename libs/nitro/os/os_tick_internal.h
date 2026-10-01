#ifndef NITRO_OS_TICK_INTERNAL_H
#define NITRO_OS_TICK_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef struct OSiTickState {
    u16 useTick;
    u16 padding;
    BOOL needResetTimer;
    volatile u64 tickCounter;
} OSiTickState;

extern OSiTickState OSi_TickState;

BOOL OS_IsTickAvailable(void);

#endif