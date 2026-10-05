#include "nitro/types.h"

typedef struct TwoDigitValues {
    u8 first;
    u8 second;
} TwoDigitValues;

extern TwoDigitValues *data_ov001_020a04f0;
extern void ShowTwoDigitCounters(TwoDigitValues *values);

void IncrementAndShowCounter(void)
{
    TwoDigitValues *values = data_ov001_020a04f0;

    values->first++;
    ShowTwoDigitCounters(values);
}
