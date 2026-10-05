#include "nitro/types.h"

typedef struct TwoDigitValues {
    u8 first;
    u8 second;
} TwoDigitValues;

extern void *GetSceneTagTracker(void);
extern void *FindActiveRecordById(void *pool, u16 recordId);
extern void func_ov027_020b81f8(void *pool, void *record, int frame);
extern void func_ov027_020b8230(void *tracker, void *record);

void ShowTwoDigitCounters(TwoDigitValues *values)
{
    void *tracker = GetSceneTagTracker();
    void *record;
    int tens;

    tens = values->first / 10;
    if (tens != 0) {
        record = FindActiveRecordById(tracker, tens + 0x154);
        func_ov027_020b81f8(tracker, record, 1);
        func_ov027_020b8230(tracker, record);
    }
    record = FindActiveRecordById(tracker, values->first % 10 + 0x154);
    func_ov027_020b81f8(tracker, record, 3);
    func_ov027_020b8230(tracker, record);
    func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 0x150));
    tens = values->second / 10;
    if (tens != 0) {
        record = FindActiveRecordById(tracker, tens + 0x15e);
        func_ov027_020b81f8(tracker, record, 6);
        func_ov027_020b8230(tracker, record);
    }
    record = FindActiveRecordById(tracker, values->second % 10 + 0x15e);
    func_ov027_020b81f8(tracker, record, 7);
    func_ov027_020b8230(tracker, record);
}
