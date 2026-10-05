#include "nitro/types.h"

typedef struct {
    u8 pad[0x10];
    u16 activeCount;
} EventRecord;

extern EventRecord *func_ov001_0209c114(u32 id);
extern int func_ov001_0209625c(EventRecord *record, int kind, int count, int arg0, int arg1);

u32 StartStageEventInstance(u32 id, int arg0, int arg1, u16 *outHandle) {
    EventRecord *record = func_ov001_0209c114(id);
    int handle;
    if (record->activeCount == 0) {
        return 0;
    }
    if (outHandle != NULL) {
        *outHandle = 0;
    }
    handle = func_ov001_0209625c(record, 2, 1, arg0, arg1);
    if (handle != 0) {
        if (outHandle != NULL) {
            *outHandle = handle;
        }
        return id;
    }
    return 0;
}
