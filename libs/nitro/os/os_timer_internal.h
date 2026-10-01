#ifndef NITRO_OS_TIMER_INTERNAL_H
#define NITRO_OS_TIMER_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

extern u16 OSi_TimerReserved;

void OSi_SetTimerReserved(int timerNum);
void OSi_UnsetTimerReserved(int timerNum);

#endif