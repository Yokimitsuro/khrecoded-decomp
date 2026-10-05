#include "nitro/types.h"

typedef struct InputRecord {
    u16 x;
    u16 y;
    u16 touch;
    u16 invalid;
} InputRecord;

extern InputRecord *data_ov027_020ba3e0;
extern int CopyRecentInputRecords(InputRecord *records);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

void CaptureLatestOnScreenTouch(void)
{
    InputRecord records[4];
    int count;
    int i;
    int last;

    count = CopyRecentInputRecords(records);
    last = count - 1;
    for (i = last; i >= 0; i--) {
        if (records[i].invalid == 0 && records[i].x < 256 && records[i].y < 192) {
            MI_CpuCopy8(&records[i], data_ov027_020ba3e0, sizeof(InputRecord));
            return;
        }
    }
    if (count >= 1) {
        MI_CpuCopy8(&records[last], data_ov027_020ba3e0, sizeof(InputRecord));
    }
}
