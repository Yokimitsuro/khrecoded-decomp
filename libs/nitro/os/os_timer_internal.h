#ifndef NITRO_OS_TIMER_INTERNAL_H
#define NITRO_OS_TIMER_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

#define REG_OS_TM0CNT_L (*(volatile u16 *)0x04000100)
#define REG_OS_TM0CNT_H (*(volatile u16 *)0x04000102)
#define REG_OS_TM1CNT_L (*(volatile u16 *)0x04000104)
#define REG_OS_TM1CNT_H (*(volatile u16 *)0x04000106)
#define REG_OS_IF       (*(volatile u32 *)0x04000214)

extern u16 OSi_TimerReserved;

void OSi_SetTimerReserved(int timerNum);
void OSi_UnsetTimerReserved(int timerNum);
void OSi_EnterTimerCallback(int timerNum, void (*callback)(void *), void *arg);

#endif