#ifndef NITRO_RTC_H
#define NITRO_RTC_H

#include "nitro/types.h"

typedef struct RTCTime {
    u32 hour;
    u32 minute;
    u32 second;
} RTCTime;

void RTC_Init(void);
int RTC_GetTime(RTCTime *time);

#endif
