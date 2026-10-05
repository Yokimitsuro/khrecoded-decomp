#include "nitro/types.h"

typedef struct {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
} CalendarTime;

extern s16 data_02053418[2][13];
extern int func_02022584(int year);

void TimeToCalendar(u32 time, CalendarTime *tm)
{
    u32 totalSeconds = time + 0x83aa7e80;
    u32 years;
    u32 months;
    u32 days;
    u32 seconds;
    int isLeapYear;

    if (!tm) {
        return;
    }

    days = totalSeconds / 86400;
    seconds = totalSeconds % 86400;

    tm->tm_wday = (days + 1) % 7;

    years = 0;

    for (;;) {
        u32 daysThisYear = func_02022584(years) ? 366 : 365;

        if (days < daysThisYear) {
            break;
        }

        days -= daysThisYear;
        years += 1;
    }

    tm->tm_year = years;
    tm->tm_yday = days;

    months = 0;

    isLeapYear = func_02022584(years);

    for (;;) {
        u32 daysThruThisMonth = data_02053418[isLeapYear][months + 1];

        if (days < daysThruThisMonth) {
            days -= data_02053418[isLeapYear][months];
            break;
        }

        ++months;
    }

    tm->tm_mon = months;
    tm->tm_mday = days + 1;

    tm->tm_hour = seconds / 3600;

    seconds %= 3600;

    tm->tm_min = seconds / 60;
    tm->tm_sec = seconds % 60;
}
