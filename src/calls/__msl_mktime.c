#include "nitro/types.h"

typedef struct {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
} CalendarTime;

extern s16 data_02053418[];

extern int func_02022688(int *value, int divisor, int *carry);
extern BOOL CheckedMultiply(long *value, long factor);
extern long LeapDays(int year, int month);
extern BOOL TryAddInt32B(long *value, long addend);
extern void TimeToCalendar(u32 time, CalendarTime *tm);

BOOL __msl_mktime(CalendarTime *tm, u32 *outTime)
{
    long days;
    u32 seconds;
    u32 daySeconds;

    if (!tm || !outTime) {
        return FALSE;
    }

    --tm->tm_mday;

    if (!func_02022688(&tm->tm_sec, 60, &tm->tm_min)) goto fail;
    if (!func_02022688(&tm->tm_min, 60, &tm->tm_hour)) goto fail;
    if (!func_02022688(&tm->tm_hour, 24, &tm->tm_mday)) goto fail;
    if (!func_02022688(&tm->tm_mon, 12, &tm->tm_year)) goto fail;

    days = tm->tm_year;

    if (!CheckedMultiply(&days, 365)) goto fail;
    if (!TryAddInt32B(&days, LeapDays(tm->tm_year, tm->tm_mon))) goto fail;
    if (!TryAddInt32B(&days, data_02053418[tm->tm_mon])) goto fail;
    if (!TryAddInt32B(&days, tm->tm_mday)) goto fail;

    if (days < 0 || days > (0xFFFFFFFFUL / 86400)) {
        goto fail;
    }

    daySeconds = days * 86400;
    seconds = (tm->tm_hour * 3600) + (tm->tm_min * 60) + tm->tm_sec;

    if (seconds > 0xFFFFFFFFUL - daySeconds) {
        goto fail;
    }

    seconds += daySeconds;
    *outTime = seconds + 0x7c558180;

    TimeToCalendar(*outTime, tm);

    return TRUE;

fail:
    return FALSE;
}
