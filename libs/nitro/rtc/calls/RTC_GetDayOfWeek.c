#include "libs/nitro/rtc/rtc_internal.h"

RTCWeek RTC_GetDayOfWeek(RTCDate *date)
{
    int century;
    int year = 2000 + (int)date->year;
    int month = (int)date->month;
    int day = (int)date->day;

    month -= 2;
    if (month < 1) {
        month += 12;
        --year;
    }

    century = year / 100;
    year %= 100;
    return (RTCWeek)(
        ((26 * month - 2) / 10 + day + year + year / 4 +
         century / 4 + 5 * century) % 7);
}
